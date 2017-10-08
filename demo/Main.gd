extends Spatial

var arvr_interface = null

func _ready():
	var test_interface = ARVRInterfaceGDNative.new()
	test_interface.set_gdnative_library(preload("res://arvrsimple.tres"))
	
	print("Test " + test_interface.get_name())
	
#	arvr_interface = preload("res://ARVRSimple.gdns").new()
#	arvr_interface = ARVRServer.find_interface("ARVRSimple")
	arvr_interface = ARVRServer.get_interface(ARVRServer.get_interface_count()-1)
	if arvr_interface and arvr_interface.initialize():
		get_viewport().arvr = true
		
		#this needs to move into the interface itself
		#ARVRServer.set_primary_interface(arvr_interface)
