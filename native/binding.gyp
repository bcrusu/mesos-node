{
	"targets": [
	{
		"target_name": "mesosApi",
		"sources": [ "src/hello.cpp", 
			"src/hello2.cpp", 
			"src/Common.cpp" ],
		"include_dirs": [ "<!(node -e \"require('nan')\")",
			"/home/bcrusu/work/github/mesos/build/3rdparty/libprocess/3rdparty/protobuf-2.5.0/src/",
			"/home/bcrusu/work/github/mesos/include",
			"/home/bcrusu/work/github/mesos/build/include" ],
		"libraries": [ "-lmesos" ],
		"link_settings": { "libraries": [ '-L/home/bcrusu/work/github/mesos/build/src/.libs' ] }
    }
  ]
}
