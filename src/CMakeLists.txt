SET(SOURCE
	SystemCommandsProcessor.cpp
	Connection.cpp
    Scraper.cpp
	Module.cpp
	CommandModule.cpp
	BotCore.cpp
	Channel.cpp
	main.cpp
)

SET(HEADERS
	SystemCommandModule.h
	SystemCommandsProcessor.h
	Connection.h
    Scraper.h
	Module.h
	CommandModule.h
	BotCore.h
	Channel.h
)

ADD_SUBDIRECTORY (modules)
LIST (APPEND SOURCE ${MODULES_SOURCE})
LIST (APPEND HEADERS ${MODULES_HEADERS})

SOURCE_GROUP (modules FILES ${MODULES_SOURCE} ${MODULES_HEADERS})

add_executable (RoboSenpai ${SOURCE} ${HEADERS})

target_link_libraries (RoboSenpai ${LIBS})
