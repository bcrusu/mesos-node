{
	"targets": [
	{
		"target_name": "mesosApi",
		"sources": [ "src/native/Addon.cpp",
			"src/native/Common.cpp", 
			"src/native/NodeExecutor.cpp", 
			"src/native/NodeExecutorDriver.cpp", 
			"src/native/NodeScheduler.cpp", 
			"src/native/NodeSchedulerDriver.cpp" ],
		"include_dirs": [ "<!(node -e \"require('nan')\")",
			"/home/bcrusu/work/github/mesos/build/3rdparty/libprocess/3rdparty/protobuf-2.5.0/src/",
			"/home/bcrusu/work/github/mesos/include",
			"/home/bcrusu/work/github/mesos/build/include" ],
		"libraries": [ "-lmesos" ],
		"link_settings": { "libraries": [ '-L/home/bcrusu/work/github/mesos/build/src/.libs' ] }
    }
  ]
}
