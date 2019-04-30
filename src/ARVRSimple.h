////////////////////////////////////////////////////////////////////////////
// This is just an example ARVR GDNative module. It does very little VR-ish
// It also outputs lots of debugging stuff which should not be in a proper
// module :)

// Written by Bastiaan "Mux213" Olij, with loads of help from Thomas "Karroffel" Herzog

#ifndef ARVR_SIMPLE_H
#define ARVR_SIMPLE_H

#include "GodotCalls.h"
#include "ARVRInterface.h"

// declare our public functions for our ARVR Interface
#ifdef __cplusplus
extern "C" {
#endif

void GDN_EXPORT godot_openvr_gdnative_singleton();
void GDN_EXPORT godot_openvr_nativescript_init(void *p_handle);

#ifdef __cplusplus
}
#endif

#endif /* !ARVR_SIMPLE_H */
