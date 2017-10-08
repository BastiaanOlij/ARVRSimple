////////////////////////////////////////////////////////////////////////////
// This is just an example ARVR GDNative module. It does very little VR-ish
// It also outputs lots of debugging stuff which should not be in a proper
// module :)

// Written by Bastiaan "Mux213" Olij, with loads of help from Thomas "Karroffel" Herzog


// #include <gdnative_api_struct.h>
#include <gdnative_api_struct.gen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvr_data_struct {
	bool is_initialised;
} arvr_data_struct;

const godot_gdnative_api_struct *api = NULL;
static godot_object *_arvr_server = NULL;

void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *p_options) {
	api = p_options->api_struct;
	_arvr_server = api->godot_global_get_singleton((char *) "ARVRServer");
}

void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *p_options) {
	api = NULL;
}

void GDN_EXPORT godot_nativescript_init(void *p_handle) {

}

void *arvr_constructor(void *p_object) {
	godot_string ret;

	printf("ARVRSimple.arvr_constructor()\n");

	arvr_data_struct *arvr_data = api->godot_alloc(sizeof(arvr_data_struct));
	arvr_data->is_initialised = false;

	printf("Allocated data at %p\n", arvr_data);

	return arvr_data;
}

void arvr_destructor(void *p_object, void *p_data) {
	printf("ARVRSimple.arvr_destructor()\n");

	if (p_data != NULL) {
		printf("Freeing data at %p\n", p_data);

		api->godot_free(p_data);
	}
}

godot_string arvr_get_name(void *p_object, void *p_data) {
	godot_string ret;

	printf("ARVRSimple.arvr_get_name(%p, %p)\n", p_object, p_data);
	char name[] = "ARVRSimple";
	api->godot_string_new_data(&ret, name, strlen(name));

	return ret;
}

godot_int arvr_get_capabilities(void *p_object, void *p_data) {
	godot_int ret;

	printf("ARVRSimple.arvr_get_capabilities()\n");
	ret = 2; // 2 = ARVR_STEREO

	return ret;
};

godot_bool arvr_get_anchor_detection_is_enabled(void *p_object, void *p_data) {
	godot_bool ret;

	printf("ARVRSimple.arvr_get_anchor_detection_is_enabled()\n");
	ret = false; // does not apply here

	return ret;
};

void arvr_set_anchor_detection_is_enabled(void *p_object, void *p_data, bool p_enable) {
	printf("ARVRSimple.arvr_set_anchor_detection_is_enabled()\n");

	// we ignore this, not supported in this interface!
};

godot_bool arvr_is_stereo(void *p_object, void *p_data) {
	godot_bool ret;

	printf("ARVRSimple.arvr_is_stereo()\n");
	ret = true;

	return ret;
};

godot_bool arvr_is_initialized(void *p_object, void *p_data) {
	godot_bool ret;
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

	printf("ARVRSimple.arvr_is_initialized()\n");
	ret = arvr_data == NULL ? false : arvr_data->is_initialised;

	return ret;
};

/*

godot_variant ARVRSimple_is_initialized(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	godot_variant ret;
	user_data_struct * user_data = (user_data_struct *) p_user_data;

	printf("ARVRSIMPLE.is_initialized()\n");
	api->godot_variant_new_bool(&ret, user_data->is_initialised);

	return ret;
};

godot_variant ARVRSimple_initialize(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	godot_variant ret;
	user_data_struct * user_data = (user_data_struct *) p_user_data;

	printf("ARVRSIMPLE.initialize()\n");

	if (!user_data->is_initialised) {
		// initialise this interface

		///@TODO how to do this in GDNative?
		// ARVRServer *arvr_server = ARVRServer::get_singleton();
		// arvr_server->set_primary_interface(this);

		user_data->is_initialised = true;
	};

	// and return our result
	api->godot_variant_new_bool(&ret, user_data->is_initialised);
	return ret;
};

godot_variant ARVRSimple_uninitialize(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	godot_variant ret;
	user_data_struct * user_data = (user_data_struct *) p_user_data;

	printf("ARVRSIMPLE.uninitialize()\n");

	if (user_data->is_initialised) {
		// cleanup if needed

		user_data->is_initialised = false;
	};

	// This shouldn't need a return variable but not sure how to set that up yet so just return true
	api->godot_variant_new_bool(&ret, true);
	return ret;
};

godot_variant ARVRSimple_get_recommended_render_targetsize(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	godot_variant ret;
	godot_vector2 size;

	printf("ARVRSIMPLE.get_recommended_render_targetsize()\n");

	api->godot_vector2_new(&size, 500, 500);
	api->godot_variant_new_vector2(&ret, &size);

	return ret;
};

godot_variant ARVRSimple_get_transform_for_eye(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	godot_variant ret;
	godot_transform transform;

	printf("ARVRSIMPLE.get_transform_for_eye()\n");

	api->godot_transform_new_identity(&transform);
	api->godot_variant_new_transform(&ret, &transform);

	return ret;
};

godot_variant ARVRSimple_get_projection_for_eye(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	godot_variant ret;
	godot_pool_real_array projection;

	printf("ARVRSIMPLE._get_projection_for_eye()\n");
	api->godot_variant_new_pool_real_array(&ret, &projection);

	return ret;
};

godot_variant ARVRSimple_commit_for_eye(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	godot_variant ret;

	printf("ARVRSIMPLE.commit_for_eye()\n");

	// This shouldn't need a return variable but not sure how to set that up yet so just return true
	api->godot_variant_new_bool(&ret, true);
	return ret;
};

godot_variant ARVRSimple_process(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	godot_variant ret;

	printf("ARVRSIMPLE.process()\n");

	// This shouldn't need a return variable but not sure how to set that up yet so just return true
	api->godot_variant_new_bool(&ret, true);
	return ret;
};

void GDN_EXPORT godot_nativescript_init(void *p_handle) {
	{
		godot_instance_create_func create = {};
		create.create_func = &ARVRSimple_constructor;

		godot_instance_destroy_func destroy = {};
		destroy.destroy_func = &ARVRSimple_destructor;

		api->godot_nativescript_register_class(p_handle, "ARVRSimple", "ARVRScriptInterface", create, destroy);		
	}

	{
		godot_instance_method get_data = {};
		get_data.method = &ARVRSimple_get_name;

		godot_method_attributes attributes = {};
		attributes.rpc_type = GODOT_METHOD_RPC_MODE_DISABLED;

		api->godot_nativescript_register_method(p_handle, "ARVRSimple", "get_name", attributes, get_data);
	}

	{
		godot_instance_method get_data = {};
		get_data.method = &ARVRSimple_get_capabilities;

		godot_method_attributes attributes = {};
		attributes.rpc_type = GODOT_METHOD_RPC_MODE_DISABLED;

		api->godot_nativescript_register_method(p_handle, "ARVRSimple", "capabilities", attributes, get_data);
	}

	{
		godot_instance_method get_data = {};
		get_data.method = &ARVRSimple_is_stereo;

		godot_method_attributes attributes = {};
		attributes.rpc_type = GODOT_METHOD_RPC_MODE_DISABLED;

		api->godot_nativescript_register_method(p_handle, "ARVRSimple", "is_stereo", attributes, get_data);
	}

	{
		godot_instance_method get_data = {};
		get_data.method = &ARVRSimple_is_initialized;

		godot_method_attributes attributes = {};
		attributes.rpc_type = GODOT_METHOD_RPC_MODE_DISABLED;

		api->godot_nativescript_register_method(p_handle, "ARVRSimple", "is_initialized", attributes, get_data);
	}

	{
		godot_instance_method get_data = {};
		get_data.method = &ARVRSimple_initialize;

		godot_method_attributes attributes = {};
		attributes.rpc_type = GODOT_METHOD_RPC_MODE_DISABLED;

		api->godot_nativescript_register_method(p_handle, "ARVRSimple", "initialize", attributes, get_data);
	}

	{
		godot_instance_method get_data = {};
		get_data.method = &ARVRSimple_uninitialize;

		godot_method_attributes attributes = {};
		attributes.rpc_type = GODOT_METHOD_RPC_MODE_DISABLED;

		api->godot_nativescript_register_method(p_handle, "ARVRSimple", "uninitialize", attributes, get_data);
	}

	{
		godot_instance_method get_data = {};
		get_data.method = &ARVRSimple_get_recommended_render_targetsize;

		godot_method_attributes attributes = {};
		attributes.rpc_type = GODOT_METHOD_RPC_MODE_DISABLED;

		api->godot_nativescript_register_method(p_handle, "ARVRSimple", "get_recommended_render_targetsize", attributes, get_data);
	}

	{
		godot_instance_method get_data = {};
		get_data.method = &ARVRSimple_get_transform_for_eye;

		godot_method_attributes attributes = {};
		attributes.rpc_type = GODOT_METHOD_RPC_MODE_DISABLED;

		api->godot_nativescript_register_method(p_handle, "ARVRSimple", "get_transform_for_eye", attributes, get_data);
	}

	{
		godot_instance_method get_data = {};
		get_data.method = &ARVRSimple_get_projection_for_eye;

		godot_method_attributes attributes = {};
		attributes.rpc_type = GODOT_METHOD_RPC_MODE_DISABLED;

		api->godot_nativescript_register_method(p_handle, "ARVRSimple", "_get_projection_for_eye", attributes, get_data);
	}

	{
		godot_instance_method get_data = {};
		get_data.method = &ARVRSimple_commit_for_eye;

		godot_method_attributes attributes = {};
		attributes.rpc_type = GODOT_METHOD_RPC_MODE_DISABLED;

		api->godot_nativescript_register_method(p_handle, "ARVRSimple", "commit_for_eye", attributes, get_data);
	}

	{
		godot_instance_method get_data = {};
		get_data.method = &ARVRSimple_process;

		godot_method_attributes attributes = {};
		attributes.rpc_type = GODOT_METHOD_RPC_MODE_DISABLED;

		api->godot_nativescript_register_method(p_handle, "ARVRSimple", "process", attributes, get_data);
	}

	///@TODO should make an instance of this interface and register it with our ARVRServer, need to find out how :)
}
*/
