#include "scop.h"
#include "scop_struct.h"
#include "shaders.h"
#include "vertexShaders.h"
#include "fragmentShaders.h"
#include "events.h"

#include <stdio.h>
#include <string.h>

void init_fail(const char *err_msg)
{
	fprintf(stderr, "%s\n", err_msg);
	glfwTerminate();
	exit(1);
}

void create_window(GLFWwindow **window) {
	*window = glfwCreateWindow(800, 800, "3D viewer", NULL, NULL);
	if (*window == NULL)
		init_fail("Failed to create GLFW window");
	glfwMakeContextCurrent(*window);
}

void init_glfw()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // CORE_PROFILE will cause errors during calls to deprecated functions
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Something for macOS TODO: check what is this
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
}

void init_glew()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		init_fail("Failed to init GLEW");
}

void init_viewport(GLFWwindow *window)
{
	int	width;
	int height;

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.f);
}

void init_culling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
}

void init_depth()
{
	static const float z_depth_near = 0.f;
	static const float z_depth_far = 1.f;
	static const float depth_clear_value = 1.f;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(z_depth_near, z_depth_far);
	glClearDepth(depth_clear_value);
}

// SCOP BEGIN

#include "calculations.h"

static const t_mat4f g_identity_matrix = {
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f
};

void init_cam_to_clip_matrix(t_mat4f *cam_to_clip)
{
	static const float	z_near = 1.f;
	static const float	z_far = 450.f;
	static const float	fov_deg = 45.f;
	float 				frustum_scale;

	frustum_scale = calc_frustum_scale(fov_deg);
	memcpy(cam_to_clip, &g_identity_matrix, sizeof(t_mat4f));
	cam_to_clip->x.x = frustum_scale;
	cam_to_clip->y.y = frustum_scale;
	cam_to_clip->z.z = (z_far + z_near) / (z_near - z_far);
	cam_to_clip->z.w = -1;
	cam_to_clip->w.z = (2 * z_far * z_near) / (z_near - z_far);
}

void init_model_to_cam_matrix(t_mat4f *model_to_cam)
{
	memcpy(model_to_cam, &g_identity_matrix, sizeof(t_mat4f));
}

void init_transform(t_transform *transform)
{
	memcpy(&transform->scale, &g_identity_matrix, sizeof(t_mat4f));
	memcpy(&transform->translate, &g_identity_matrix, sizeof(t_mat4f));
	memcpy(&transform->rotate, &g_identity_matrix, sizeof(t_mat4f));
	memcpy(&transform->strp, &g_identity_matrix, sizeof(t_mat4f));
	transform->translate.w.z = -10.f;
	transform->strp.w.z = -10.f;
}

void init_matrices(t_matrices *mat)
{
	init_cam_to_clip_matrix(&mat->cam_to_clip);
	init_model_to_cam_matrix(&mat->model_to_cam);
	init_transform(&mat->transf);
}

void init_shaders(t_shaders *shaders)
{
	static const int total_shaders_count = 1;

	shaders->count = total_shaders_count;
	shaders->arr = malloc(sizeof(*shaders->arr) * shaders->count);
	if (!shaders->arr)
		init_fail("Not enough memory");
	shaders->arr[0] = create_shader_program_vert_frag(vertex_shader_pass_vtn,
													  fragment_shader_pass_vtn);
	shaders->cur = shaders->arr[0];
	update_uniforms_locations(shaders);
}

void init_buf_objects(t_buf_objects *bufs)
{
	glGenBuffers(1, &bufs->vbo);
	glGenBuffers(1, &bufs->ibo);
	glGenVertexArrays(1, &bufs->vao); // TODO: check if protect?
}

void init_keys(t_keys *keys)
{
	keys->right = 0;
	keys->left = 0;
	keys->back = 0;
	keys->forward = 0;
	keys->up = 0;
	keys->down = 0;
	keys->enable_rotation = 0;
	keys->change_cull = 0;
	keys->draw_points;
	keys->draw_lines;
	keys->draw_triangles;
}

void init_states(t_states *states)
{
	states->enable_rotation = 1;
	states->culling = GL_FRONT;
	states->draw_type = GL_TRIANGLES;
}

void init_scop(t_scop *scop)
{
	scop->obj = NULL;
	init_matrices(&scop->mat);
	init_shaders(&scop->shaders);
	init_buf_objects(&scop->bufs);
	init_keys(&scop->keys);
	init_states(&scop->state);
}

// SCOP END

void initialization(t_scop *scop)
{
	init_glfw();
	create_window(&scop->window);
	init_glew();
	init_viewport(scop->window);
	init_culling();
	init_depth();
	register_callbacks(scop->window);
	init_scop(scop);
}
