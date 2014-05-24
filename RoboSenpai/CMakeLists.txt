add_executable (bot BotCore.cpp Channel.cpp SystemCommandsProcessor.cpp main.cpp)
target_link_libraries(bot ${LIBS})
