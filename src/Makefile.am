INCLUDES = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-I$(top_srcdir)/include

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = \
	libogreopcode.la

libogreopcode_la_SOURCES = \
	BP_Endpoint.cpp   \
	BP_Proxy.cpp   \
	BP_Scene.cpp   \
	IOgreCollisionShape.cpp   \
	OgreBoxCollisionShape.cpp   \
	OgreCapsuleMeshCollisionShape.cpp   \
	OgreCollisionContext.cpp   \
	OgreCollisionManager.cpp   \
	OgreCollisionObject.cpp   \
	OgreEntityCollisionShape.cpp   \
	OgreMeshCollisionShape.cpp   \
	OgreOpcodeCharacterController.cpp   \
	OgreOpcodeDebugObject.cpp   \
	OgreOpcodeLine.cpp   \
	OgreOpcodeMath.cpp   \
	OgreOpcodeRay.cpp   \
	OgreOpcodeTerrainData.cpp   \
	OgreOrientedBox.cpp   \
	OgrePtrCollisionShape.cpp   \
	OgreSphereMeshCollisionShape.cpp   \
	OgreTerrainCollisionShape.cpp   \
	OgreTriangle.cpp

libogreopcode_la_LDFLAGS = \
	$(OGRE_LIBS) \
	-version-info @OGREOPCODE_VERSION_INFO@

libogreopcode_la_CXXFLAGS = \
	$(OGRE_CFLAGS)

libogreopcode_la_LIBADD = \
	Opcode/libopcode.la

SUBDIRS = \
	Opcode

