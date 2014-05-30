# Locate pugixml
#
# This module defines
#   PUGIXML_FOUND, if false, do not try to link pugixml
#   PUGIXML_LIBRARY, where to find pugixml
#   PUGIXML_INCLUDE_DIR, where to find pugixml.hpp
#
# Copyright (c) 2014 Josaphat Valdivia
#

FIND_PATH( PUGIXML_INCLUDE_DIR "pugixml.hpp")
FIND_LIBRARY( PUGIXML_LIBRARY pugixml )

if( PUGIXML_LIBRARY AND PUGIXML_INCLUDE_DIR )
	MESSAGE ( STATUS "Found pugixml: ${PUGIXML_LIBRARY}" )
	SET ( PUGIXML_FOUND )
else ( PUGIXML_LIBRARY AND PUGIXML_INCLUDE_DIR )
	MESSAGE( STATUS "Could NOT find pugixml" )
endif ( PUGIXML_LIBRARY AND PUGIXML_INCLUDE_DIR )
