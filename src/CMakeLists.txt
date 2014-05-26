add_executable (RoboSenpai BotCore.cpp Channel.cpp SystemCommandsProcessor.cpp main.cpp)

target_link_libraries(RoboSenpai ${LIBS})
