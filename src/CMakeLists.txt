SET(SOURCE
	SystemCommandsProcessor.cpp
	Connection.cpp
	BotCore.cpp
	Channel.cpp
	main.cpp
)

SET(HEADERS
	SystemCommandModule.h
	SystemCommandsProcessor.h
	Connection.h
	BotCore.h
	Channel.h
)
	
add_executable (RoboSenpai ${SOURCE} ${HEADERS})

target_link_libraries(RoboSenpai ${LIBS})
