find_program(MD2MAN NAMES md2man go-md2man md2man-roff)
if(MD2MAN)
	set(MAN_TGT ${PROJECT_NAME}.1)
	configure_file(
		${MAN_TGT}.md
		${MAN_TGT}.md.out
		@ONLY
	)
	add_custom_command(
		COMMAND ${MD2MAN} < ${MAN_TGT}.md.out > ${MAN_TGT}
		COMMENT "Building manpage ${MAN_TGT}"
		MAIN_DEPENDENCY ${MAN_TGT}.md.out
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${MAN_TGT}
		VERBATIM
	)
	add_custom_target(
		man ALL
		DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${MAN_TGT}
	)
endif()

if(MAN_TGT)
	install(
		FILES ${CMAKE_CURRENT_BINARY_DIR}/${MAN_TGT}
		DESTINATION "${CMAKE_INSTALL_MANDIR}/man1"
	)
endif()
