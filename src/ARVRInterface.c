////////////////////////////////////////////////////////////////////////////
// This is just an example ARVR GDNative module. It does very little VR-ish
// It also outputs lots of debugging stuff which should not be in a proper
// module :)

// Written by Bastiaan "Mux213" Olij, with loads of help from Thomas "Karroffel" Herzog

#include "ARVRInterface.h"

void *godot_arvr_constructor(godot_object *p_instance) {
	godot_string ret;

	arvr_data_struct *arvr_data = api->godot_alloc(sizeof(arvr_data_struct));
	arvr_data->instance = p_instance;
	arvr_data->is_initialised = false;
	arvr_data->iod_cm = 6.1;
	arvr_data->display_to_lens_cm = 4.0;
	arvr_data->display_width_cm = 14.0;
	arvr_data->oversample = 1.0;
	arvr_data->eye_height = 1.80;

	return arvr_data;
}

void godot_arvr_destructor(void *p_data) {
	if (p_data != NULL) {
		api->godot_free(p_data);
	}
}

godot_string godot_arvr_get_name(const void *p_data) {
	godot_string ret;

	char name[] = "ARVRSimple";
	api->godot_string_new(&ret);
	api->godot_string_parse_utf8(&ret, name);

	return ret;
}

godot_int godot_arvr_get_capabilities(const void *p_data) {
	godot_int ret;

	ret = 2; // 2 = ARVR_STEREO

	return ret;
}

godot_bool godot_arvr_get_anchor_detection_is_enabled(const void *p_data) {
	godot_bool ret;

	ret = false; // does not apply here

	return ret;
}

void godot_arvr_set_anchor_detection_is_enabled(void *p_data, bool p_enable) {
	// we ignore this, not supported in this interface!
}

godot_bool godot_arvr_is_stereo(const void *p_data) {
	godot_bool ret;

	// printf("ARVRSimple.arvr_is_stereo()\n");
	ret = true;

	return ret;
}

godot_bool godot_arvr_is_initialized(const void *p_data) {
	godot_bool ret;
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

	ret = arvr_data == NULL ? false : arvr_data->is_initialised;

	return ret;
}
 
godot_bool godot_arvr_initialize(void *p_data) {
	godot_bool ret;
	arvr_data_struct * arvr_data = (arvr_data_struct *) p_data;

	if (!arvr_data->is_initialised) {
		// initialise this interface, so initialize any 3rd party libraries, open up HMD window if required, etc.


		// note, this will be made the primary interface by ARVRInterfaceGDNative
		arvr_data->is_initialised = true;
	}

	// and return our result
	ret = arvr_data->is_initialised;
	return ret;
}

void godot_arvr_uninitialize(void *p_data) {
	arvr_data_struct * arvr_data = (arvr_data_struct *) p_data;

	if (arvr_data->is_initialised) {
		// note, this will already be removed as the primary interface by ARVRInterfaceGDNative

		// cleanup if needed

		arvr_data->is_initialised = false;
	}
}

godot_vector2 godot_arvr_get_recommended_render_targetsize(const void *p_data) {
	godot_vector2 size;

	// printf("ARVRSimple.arvr_get_recommended_render_targetsize()\n");

	api->godot_vector2_new(&size, 500, 500);

	return size;
}

godot_transform godot_arvr_get_transform_for_eye(void *p_data, godot_int p_eye, godot_transform *p_cam_transform) {
	arvr_data_struct * arvr_data = (arvr_data_struct *) p_data;
	godot_transform transform_for_eye;
	godot_transform hmd_transform;
	godot_transform reference_frame = arvr_api->godot_arvr_get_reference_frame();
	godot_transform ret;
	godot_vector3 offset;
	godot_real world_scale = arvr_api->godot_arvr_get_worldscale();

	// printf("ARVRSimple.arvr_get_transform_for_eye()\n");

	// create our transform from head center to eye
	api->godot_transform_new_identity(&transform_for_eye);
	if (p_eye == 1) {
		// left eye
		api->godot_vector3_new(&offset, -arvr_data->iod_cm * 0.01 * 0.5 * world_scale, 0.0, 0.0);
		transform_for_eye = api->godot_transform_translated(&transform_for_eye, &offset);
	} else if (p_eye == 2) {
		// right eye
		api->godot_vector3_new(&offset, arvr_data->iod_cm * 0.01 * 0.5 * world_scale, 0.0, 0.0);
		transform_for_eye = api->godot_transform_translated(&transform_for_eye, &offset);
	} else {
		// leave in the middle, mono
	}

	// now determine our HMD positional tracking, we have none in this interface...
	api->godot_transform_new_identity(&hmd_transform);
	api->godot_vector3_new(&offset, 0.0, arvr_data->eye_height * world_scale, 0.0);
	hmd_transform = api->godot_transform_translated(&hmd_transform, &offset);

	// Now construct our full transform, the order may be in reverse, have to test :)
	ret = *p_cam_transform;
	ret = api->godot_transform_operator_multiply(&ret, &reference_frame);
	ret = api->godot_transform_operator_multiply(&ret, &hmd_transform);
	ret = api->godot_transform_operator_multiply(&ret, &transform_for_eye);

	return ret;
}

void arvr_set_frustum(godot_real *p_projection, godot_real p_left, godot_real p_right, godot_real p_bottom, godot_real p_top, godot_real p_near, godot_real p_far) {

	godot_real x = 2 * p_near / (p_right - p_left);
	godot_real y = 2 * p_near / (p_top - p_bottom);

	godot_real a = (p_right + p_left) / (p_right - p_left);
	godot_real b = (p_top + p_bottom) / (p_top - p_bottom);
	godot_real c = -(p_far + p_near) / (p_far - p_near);
	godot_real d = -2 * p_far * p_near / (p_far - p_near);

	p_projection[0] = x;
	p_projection[1] = 0;
	p_projection[2] = 0;
	p_projection[3] = 0;
	p_projection[4] = 0;
	p_projection[5] = y;
	p_projection[6] = 0;
	p_projection[7] = 0;
	p_projection[8] = a;
	p_projection[9] = b;
	p_projection[10] = c;
	p_projection[11] = -1;
	p_projection[12] = 0;
	p_projection[13] = 0;
	p_projection[14] = d;
	p_projection[15] = 0;
}

void godot_arvr_fill_projection_for_eye(void *p_data, godot_real *p_projection, godot_int p_eye, godot_real p_aspect, godot_real p_z_near, godot_real p_z_far) {
	arvr_data_struct * arvr_data = (arvr_data_struct *) p_data;

	// The code below is an example of calculating our stereoscopic projections based on head mounted devices.

	// printf("ARVRSimple.arvr_return_projection_for_eye()\n");

	// we first calculate our base frustum on our values without taking our lens magnification into account.
	godot_real f1 = (arvr_data->iod_cm * 0.5) / arvr_data->display_to_lens_cm;
	godot_real f2 = ((arvr_data->display_width_cm - arvr_data->iod_cm) * 0.5) / arvr_data->display_to_lens_cm;
	godot_real f3 = (arvr_data->display_width_cm / 4.0) / arvr_data->display_to_lens_cm;

	// now we apply our oversample factor to increase our FOV. how much we oversample is always a balance we strike between performance and how much
	// we're willing to sacrifice in FOV.
	godot_real add = ((f1 + f2) * (arvr_data->oversample - 1.0)) / 2.0;
	f1 += add;
	f2 += add;

	// always apply KEEP_WIDTH aspect ratio
	f3 *= p_aspect;

	if (p_eye == 1) {
		// left eye
		arvr_set_frustum(p_projection, -f2 * p_z_near, f1 * p_z_near, -f3 * p_z_near, f3 * p_z_near, p_z_near, p_z_far);
	} else {
		// right eye
		arvr_set_frustum(p_projection, -f1 * p_z_near, f2 * p_z_near, -f3 * p_z_near, f3 * p_z_near, p_z_near, p_z_far);		
	}
}

void godot_arvr_commit_for_eye(void *p_data, godot_int p_eye, godot_rid *p_render_target, godot_rect2 *p_screen_rect) {
	// This function is responsible for outputting the final render buffer for each eye. 
	// p_screen_rect will only have a value when we're outputting to the main viewport.

	// For an interface that must output to the main viewport (such as with mobile VR) we should give an error when p_screen_rect is not set
	// For an interface that outputs to an external device we should render a copy of one of the eyes to the main viewport if p_screen_rect is set, and only output to the external device if not.

	arvr_api->godot_arvr_blit(p_eye, p_render_target, p_screen_rect);
}

void godot_arvr_process(void *p_data) {
	// this method gets called before every frame is rendered, here is where you should update tracking data, update controllers, etc.

}

const godot_arvr_interface_gdnative interface_struct = {
	GODOTVR_API_MAJOR, GODOTVR_API_MINOR,
	godot_arvr_constructor,
	godot_arvr_destructor,
	godot_arvr_get_name,
	godot_arvr_get_capabilities,
	godot_arvr_get_anchor_detection_is_enabled,
	godot_arvr_set_anchor_detection_is_enabled,
	godot_arvr_is_stereo,
	godot_arvr_is_initialized,
	godot_arvr_initialize,
	godot_arvr_uninitialize,
	godot_arvr_get_recommended_render_targetsize,
	godot_arvr_get_transform_for_eye,
	godot_arvr_fill_projection_for_eye,
	godot_arvr_commit_for_eye,
	godot_arvr_process
};
