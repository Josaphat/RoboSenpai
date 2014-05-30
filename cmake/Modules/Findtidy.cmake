# Locate tidy
#
# This module defines
#   TIDY_FOUND, if false, do not try to link tidy
#   TIDY_LIBRARY, where to find tidy
#   TIDY_INCLUDE_DIR, where to find tidy.h
#
# Copyright (c) 2014 Josaphat Valdivia
#

FIND_PATH ( TIDY_INCLUDE_DIR "tidy.h" )
FIND_LIBRARY ( TIDY_LIBRARY tidy )

if ( TIDY_LIBRARY AND TIDY_INCLUDE_DIR )
	MESSAGE ( STATUS "Found tidy: ${TIDY_LIBRARY}" )
	SET ( PUGIXML_FOUND )
else ( TIDY_LIBRARY AND TIDY_INCLUDE_DIR )
	MESSAGE ( STATUS "Could NOT find tidy" )
endif ( TIDY_LIBRARY AND TIDY_INCLUDE_DIR )
