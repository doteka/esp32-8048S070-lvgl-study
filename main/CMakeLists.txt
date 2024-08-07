idf_component_register(
    SRCS
        "main.c"
        "ui/ui.c"
        "ui/ui_helpers.c"
        "ui/screens/ui_Screen1.c"
        "ui/screens/ui_Screen2.c"
        "ui/screens/modal.c"
        "ui/screens/setup_set.c"
        "ui/screens/tabview_setup.c"
        "ui/screens/tabview_grid.c"
        "ui/screens/simple_card_game.c"
        "ui/screens/simple_card_game_init.c"
        "ui/screens/charts.c"
        "ui/screens/pulse.c"
        "ui/screens/segment_font.c"
        "ui/screens/fs_test.c"
    INCLUDE_DIRS
        "."
    REQUIRES spi_flash
    REQUIRES nvs_flash
    REQUIRES spiffs
    REQUIRES fatfs
    REQUIRES vfs
)
# 파티션 테이블 파일 설정
# set(partition_table_file "${CMAKE_SOURCE_DIR}/partitions.csv")
# set(PARTITION_TABLE_FILENAME ${partition_table_file})

# # 파티션 테이블 파일 설정
# set(ESP32_FLASH_VARS
#     PARTITION_TABLE_FILENAME
# )