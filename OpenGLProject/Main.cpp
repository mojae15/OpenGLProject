
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const char *vertexShaderSource = "#version 450 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main(){\n"
                                 "	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 450 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main(){\n"
                                   "	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n";

void framebuffer_size_callback( GLFWwindow *window, int width, int height );
void processInput( GLFWwindow *window );

// settings

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int main() {

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 5 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

#ifdef __APPLE__
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL );
    if ( window == NULL ) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent( window );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Build shaders
    // ---------------------------------------
    // Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
    glCompileShader( vertexShader );

    //Check if the shader succesfully compiled
    int vertexSuccess;
    char vertexLog[512];
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &vertexSuccess );
    if ( !vertexSuccess ) {
        glGetShaderInfoLog( vertexShader, 512, NULL, vertexLog );
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << vertexLog << std::endl;
    }

    // Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &fragmentShaderSource, NULL );
    glCompileShader( fragmentShader );

    //Check if the shader succesfully compiled
    int fragmentSuccess;
    char fragmentLog[512];
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess );
    if ( !fragmentSuccess ) {
        glGetShaderInfoLog( fragmentShader, 512, NULL, fragmentLog );
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << fragmentLog << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );

    int linkSuccess;
    char linkLog[512];
    glGetProgramiv( shaderProgram, GL_LINK_STATUS, &linkSuccess );
    if ( !linkSuccess ) {
        glGetProgramInfoLog( shaderProgram, 512, NULL, linkLog );
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << linkLog << std::endl;
    }

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    float vertices[] = {
        // top right
        0.5f, 0.5f, 0.0f,
        //bottom right
        0.5f, -0.5f, 0.0f,
        // bottom left
        -0.5f, -0.5f, 0.0f,
        // top left
        -0.5f, 0.5f, 0.0f };

    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int VBO, VAO, EBO;
    glGenBuffers( 1, &VBO );
    glGenBuffers( 1, &EBO );
    glGenVertexArrays( 1, &VAO );

    glBindVertexArray( VAO );

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void *)0 );
    glEnableVertexAttribArray( 0 );


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // render loop
    // -----------
    while ( !glfwWindowShouldClose( window ) ) {
        // input
        // -----
        processInput( window );

        // render
        // ------
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        // Draw Triangle
        glUseProgram( shaderProgram );
        glBindVertexArray( VAO );
        // glDrawArrays( GL_TRIANGLES, 0, 3 );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput( GLFWwindow *window ) {
    if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
        glfwSetWindowShouldClose( window, true );
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback( GLFWwindow *window, int width, int height ) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport( 0, 0, width, height );
}
