# =====================================================================================================================
# MIT License
# 
# Copyright (c) 2022 Dragonscale-Games
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# =====================================================================================================================


# =====================================================================================================================
# File:         CMakeLists.txt
# Author:       David Cruse
# Email:        dragonscale.games.llc@gmail.com
# Date:         5/5/2022
# =====================================================================================================================

add_executable(GlowEditor "main.cpp" 
"Editor/Editor.cpp" "Editor/Editor.hpp"
 "Registration.cpp" 
 "States/State_Main.cpp" "States/State_Main.hpp" 
 "Archetypes/ShapeArchetypes.cpp" "Archetypes/ShapeArchetypes.hpp")

target_link_libraries(GlowEditor PUBLIC BarrageCore curlpp)
target_include_directories(GlowEditor PUBLIC "${CMAKE_SOURCE_DIR}")
target_include_directories(GlowEditor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(GlowEditor PUBLIC "${CMAKE_SOURCE_DIR}/BarrageEngine")

file(COPY "${CMAKE_SOURCE_DIR}/Assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/ThirdParty/curlpp/curlpp.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")