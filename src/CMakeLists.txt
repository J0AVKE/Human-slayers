add_executable(MyExecutable
	main.cpp
	Entities/Animations.cpp
    #Entities/Tilemap.cpp
    Entities/Collisions.cpp
    Entities/Enemy.cpp
    Entities/Health.cpp
)

target_include_directories(MyExecutable PRIVATE
	"${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(MyExecutable PRIVATE 
	SDL3::SDL3
	SDL3_image::SDL3_image
)
