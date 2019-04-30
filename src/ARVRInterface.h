////////////////////////////////////////////////////////////////////////////
// This is just an example ARVR GDNative module. It does very little VR-ish
// It also outputs lots of debugging stuff which should not be in a proper
// module :)

// Written by Bastiaan "Mux213" Olij, with loads of help from Thomas "Karroffel" Herzog

#ifndef ARVR_INTERFACE_H
#define ARVR_INTERFACE_H

#include "GodotCalls.h"

extern const godot_arvr_interface_gdnative interface_struct;

typedef struct arvr_data_struct {
	godot_object * instance;
	bool is_initialised;
	float iod_cm;
	float display_to_lens_cm;
	float display_width_cm;
	float oversample;
	float eye_height;
} arvr_data_struct;

#endif /* !ARVR_INTERFACE_H */
