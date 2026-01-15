//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



const unsigned int width = 800;
const unsigned int height = 800;



// Vertices coordinates
/*
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

*/


GLfloat vertices[] =
{
	// [พิกัด X, Y, Z]          [สี R, G, B]             [พิกัด Texture U, V]
	// --- ตัวหีบ (Base 0-7) - สีน้ำตาลเข้ม ---
	-0.6f, -0.4f,  0.4f,     0.4f, 0.2f, 0.0f,       0.00f, 0.00f, // 0
	 0.6f, -0.4f,  0.4f,     0.4f, 0.2f, 0.0f,       0.25f, 0.00f, // 1
	 0.6f,  0.1f,  0.4f,     0.4f, 0.2f, 0.0f,       0.25f, 0.20f, // 2
	-0.6f,  0.1f,  0.4f,     0.4f, 0.2f, 0.0f,       0.00f, 0.20f, // 3
	-0.6f, -0.4f, -0.4f,     0.4f, 0.2f, 0.0f,       0.25f, 0.00f, // 4
	 0.6f, -0.4f, -0.4f,     0.4f, 0.2f, 0.0f,       0.50f, 0.00f, // 5
	 0.6f,  0.1f, -0.4f,     0.4f, 0.2f, 0.0f,       0.50f, 0.20f, // 6
	-0.6f,  0.1f, -0.4f,     0.4f, 0.2f, 0.0f,       0.25f, 0.20f, // 7

	// --- ฝาหีบ หน้า (8-13) - สีแดง ---
	-0.6f,  0.101f,  0.4f,   1.0f, 0.0f, 0.0f,       0.00f, 0.25f, // 8
	 0.6f,  0.101f,  0.4f,   1.0f, 0.0f, 0.0f,       0.25f, 0.25f, // 9
	 0.55f, 0.35f,   0.4f,   1.0f, 0.0f, 0.0f,       0.20f, 0.40f, // 10
	-0.55f, 0.35f,   0.4f,   1.0f, 0.0f, 0.0f,       0.05f, 0.40f, // 11
	 0.3f,  0.5f,    0.4f,   1.0f, 0.0f, 0.0f,       0.15f, 0.50f, // 12
	-0.3f,  0.5f,    0.4f,   1.0f, 0.0f, 0.0f,       0.10f, 0.50f, // 13

	// --- ฝาหีบ หลัง (14-19) - สีเขียว ---
	-0.6f,  0.101f, -0.4f,   0.0f, 1.0f, 0.0f,       0.25f, 0.25f, // 14
	 0.6f,  0.101f, -0.4f,   0.0f, 1.0f, 0.0f,       0.50f, 0.25f, // 15
	 0.55f, 0.35f,  -0.4f,   0.0f, 1.0f, 0.0f,       0.45f, 0.40f, // 16
	-0.55f, 0.35f,  -0.4f,   0.0f, 1.0f, 0.0f,       0.30f, 0.40f, // 17
	 0.3f,  0.5f,   -0.4f,   0.0f, 1.0f, 0.0f,       0.40f, 0.50f, // 18
	-0.3f,  0.5f,   -0.4f,   0.0f, 1.0f, 0.0f,       0.35f, 0.50f  // 19
};


// Indices for vertices order
/*
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};
*/


GLuint indices[] =
{
	// --- Base ---
	0, 1, 2,   2, 3, 0,       // หน้า (น้ำตาล)
	5, 4, 7,   7, 6, 5,       // หลัง (น้ำตาล)
	4, 0, 3,   3, 7, 4,       // ซ้าย (น้ำตาล)
	1, 5, 6,   6, 2, 1,       // ขวา (น้ำตาล)
	0, 4, 5,   5, 1, 0,       // ล่าง (น้ำตาล)

	// --- Lid Front (หน้าฝา - แดง) ---
	8, 9, 10,   10, 11, 8,    // ส่วนล่าง
	11, 10, 12, 12, 13, 11,   // ส่วนบน

	// --- Lid Back (หลังฝา - เขียว) ---
	15, 14, 17,  17, 16, 15,  // ส่วนล่าง
	17, 19, 18,  18, 16, 17,  // ส่วนบน

	// --- Lid Sides (แผ่นเชื่อมหน้าแดง-หลังเขียว) ---
	8, 14, 17,  17, 11, 8,    // ข้างซ้ายล่าง
	11, 17, 19, 19, 13, 11,   // ข้างซ้ายบน
	13, 19, 18, 18, 12, 13,   // ยอดบน
	12, 18, 16, 16, 10, 12,   // ข้างขวาบน
	10, 16, 15, 15, 9, 10     // ข้างขวาล่าง
};


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "OpenGL_Basic"
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL_Basic", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");



	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/

	// ใช้ fs::path จะช่วยจัดการเรื่องเครื่องหมาย / หรือ \ ให้เราเองอัตโนมัติ
//	std::string parentDir = (fs::current_path().fs::path::parent_path()).string(); // อยู่ที่ Opengl_basic_
//	std::string texPath =  "/Resources/basic_opengl_7_Going 3D/";

	// แปลงเป็น string เพื่อส่งให้ Texture class
// Texture
//	Texture brickTex((parentDir + texPath + "brick.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
//	brickTex.texUnit(shaderProgram, "tex0", 0);


	// 1. ดึงตำแหน่งที่ไฟล์ .exe ทำงานอยู่
	fs::path currentPath = fs::current_path();

	// 2. ใช้เครื่องหมาย / ในการ "ต่อ" โฟลเดอร์ (fs::path จะจัดการเครื่องหมาย \ ให้เองตาม OS)
	// สมมติว่า Resources อยู่ในโฟลเดอร์เดียวกับ .exe ของคุณ
	fs::path fullPath = currentPath / "Resources" / "basic_opengl_7_Going_3D" / "brick.png";

	// แต่ถ้า Resources อยู่ "ข้างนอก" โฟลเดอร์ที่ .exe อยู่ (ต้องถอย 1 ก้าว) ให้ใช้:
	// fs::path fullPath = currentPath.parent_path() / "Resources" / "basic_opengl_7_Going_3D" / "brick.png";

	// 3. แปลงเป็น string เพื่อส่งให้ Class Texture
	std::string finalPath = fullPath.string();

	// เช็คเพื่อความชัวร์ (แนะนำให้ใส่ไว้ตลอดเวลาเรียน จะได้รู้ทันทีถ้าพังที่ Path)
	if (fs::exists(fullPath)) {
		std::cout << "SUCCESS: Found texture at: " << finalPath << std::endl;
	}
	else {
		std::cout << "ERROR: File not found! Current location is: " << currentPath << std::endl;
	}

	// 4. ส่งเข้า Texture Class
	//Texture brickTex(finalPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//brickTex.texUnit(shaderProgram, "tex0", 0);




	//Texture popCat(finalPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);


	// Texture
	//Texture popCat((parentDir + texPath + "pop_cat.png").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//popCat.texUnit(shaderProgram, "tex0", 0);

	// Original code from the tutorial
	//Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	//popCat.texUnit(shaderProgram, "tex0", 0);

		// Variables that help the rotation of the pyramid
	float rotation = 0.0f;
	double prevTime = glfwGetTime();



	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Simple timer
		// 1. ดึงเวลาปัจจุบัน
		double crntTime = glfwGetTime();

		// 2. เช็คว่าเวลาผ่านไปครบกำหนดหรือยัง (เปลี่ยน 1 / 60 เป็น 1.0 / 60.0)
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.01f;   // <<--- แก้ตรงนี้! (เดิมคือ 0.5f)
								// ยิ่งค่าน้อยยิ่งหมุนช้า เช่น 0.05f หรือ 0.1f
			prevTime = crntTime;
		}


		// Initializes matrices so they are not the null matrix
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);


		//Assigns different transformations to each matrix
		//model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		// 1. สั่งให้หันข้าง (หมุนรอบแกน Y)
		// ลองเปลี่ยน 45.0f เป็น 90.0f หรือมุมที่ต้องการครับ
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		// ปรับค่า Y จาก -0.5f เป็น 0.0f เพื่อให้วัตถุอยู่กึ่งกลางสายตาพอดี
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
		//view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);


		// Outputs the matrices into the Vertex
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		// Binds texture so that is appears in rendering
		//popCat.Bind();
		//brickTex.Bind();
		// 
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// 
		// 
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();



	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	//brickTex.Delete();
	//popCat.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}