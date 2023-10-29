#include "StreamGUI.h"


static void glfw_error_callback(int error, const char* description){
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GUI::GUI(): m_clear_color(0.45f, 0.55f, 0.60f, 1.00f){
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        std::cerr << "Unable to initialize GLFW!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    m_window = glfwCreateWindow(1280, 720, m_windowTitle.data(), NULL, NULL);
    assert(m_window);

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    io.Fonts->AddFontFromFileTTF("JetBrainsMono-Regular.ttf", 24);
}

GUI::~GUI()
{
    std::cout << "Cleaning up GUI" << std::endl;

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void GUI::setBackgroundColor(float red, float green, float blue)
{
    m_clear_color.x = red;
    m_clear_color.y = green;
    m_clear_color.z = blue;
    m_clear_color.w = 1.0f; // alpha component - not using
}

void GUI::mainLoop(){
    //Set up directory arrays
    _setDirectoryArrays();
    //running loop
    while (!glfwWindowShouldClose(m_window)){
        setUpFrame();
        renderFileChooser();
        renderStatistics();
        renderFrame();
    }
    std::cout << "Exiting" << std::endl;
}

std::filesystem::path GUI::_findTestDataDir() {
    auto thePath = std::filesystem::current_path();
    //find the right directory
    while (thePath.filename() != "LakeSuperiorStream") {
        thePath = thePath.parent_path();
    }
    //go into the test data folder
    thePath.append("TestData");
    return thePath;
}

char ** GUI::listFilesInDirectory(const std::filesystem::path& directory, int &pathCount, char** &names) {

    // Count the number of regular files in the directory
    int count = 0;
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            count++;
        }
    }

    // Allocate memory for the char** array
    char** result = new char*[count + 1]; // +1 for a nullptr terminator
    names = new char*[count + 1];
    // Copy the file paths to the char** array
    int i = 0;
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            result[i] = new char[entry.path().string().size() + 1];
            std::strcpy(result[i], entry.path().string().c_str());
            names[i] = new char[entry.path().filename().string().size() + 1];
            std::strcpy(names[i], entry.path().filename().string().c_str());
            i++;
        }
    }

    result[count] = nullptr; // Add a nullptr terminator
    names[count] = nullptr; // Add a nullptr terminator
    pathCount = count;
    return result;
}

void GUI::_setDirectoryArrays() {
    //set up researcher paths
    _rPaths = listFilesInDirectory( _findTestDataDir().append("RSamples"),_rPathCount,_rNames);
    //set up sensor paths
    _sPaths = listFilesInDirectory( _findTestDataDir().append("SSamples"),_sPathCount,_sNames);
}

void GUI::renderFrame() {
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(m_clear_color.x * m_clear_color.w, m_clear_color.y * m_clear_color.w, m_clear_color.z * m_clear_color.w, m_clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_window);
}

void GUI::renderFileChooser() {
    ImGui::Begin("Sample Files", &_showInputWindow);
    //researcher drop down menu select
    ImGui::Text("Researcher File");
    ImGui::Combo("Choose One", &_rChoice, _rNames, _rPathCount);
    //sensor drop down menu select
    ImGui::Text("Sensor File");
    ImGui::Combo("Choose Another", &_sChoice, _sNames, _sPathCount);

    ImGui::End();
}

void GUI::renderStatistics() {
    //Start the frame
    ImGui::Begin("Statistics", &_showInputWindow);
    ImGui::InputText("Input Date", dateInput, IM_ARRAYSIZE(dateInput));
    if (ImGui::Button("Update")) {
        date = Time(dateInput,"00:00");
        std::cout << "Started Reading files... " << std::endl;
        readFiles();
        std::cout << "Finished Reading files..." << std::endl;
        stream = Stream(date,std::make_unique<std::vector<std::shared_ptr<ISample>>>(_rSamples),std::make_unique<std::vector<std::shared_ptr<ISample>>>(_sSamples));
        std::cout << "Updated Stream..." << std::endl;
    }
    //Make sure it exists
    if(stream.getObservation()){
        ImGui::Text("Closest Date found: ");
        ImGui::Text("%s", stream.getObservation()->getTime().toString().c_str());

        ImGui::Text("Observation Values");
        ImGui::Text("EC25 = %s", stream.getObservation()->getField(DataField::E25).c_str());
        ImGui::Text("FLOW = %s", stream.getObservation()->getField(DataField::FLOW).c_str());
        ImGui::Text("TEMP = %s", stream.getObservation()->getField(DataField::TEMP).c_str());

        ImGui::Text("Sensor Averages");
        ImGui::Text("EC25 = %f", stream.getEc25Avg());
        ImGui::Text("FLOW = %f", stream.getFlowAvg());
        ImGui::Text("TEMP = %f", stream.getTempAvg());

        ImGui::Text("Difference Between Sensor Averages and Observation Values");
        ImGui::Text("EC25 = %f", stream.getEc25Diff());
        ImGui::Text("FLOW = %f", stream.getFlowDiff());
        ImGui::Text("TEMP = %f", stream.getTempDiff());

        ImGui::Text("Flags");
        ImGui::Text("EC25: %s", stream.goodObservation(DataField::E25) ? "Good" : "FLAGGED");
        ImGui::Text("FLOW: %s", stream.goodObservation(DataField::FLOW) ? "Good" : "FLAGGED");
        ImGui::Text("TEMP: %s", stream.goodObservation(DataField::TEMP) ? "Good" : "FLAGGED");
    }
    ImGui::End();
}

void GUI::setUpFrame() {
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();

    int windowWidth = 500;
    int windowHeight = 200;
    ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_FirstUseEver);

    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 635, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
}

void GUI::readFiles() {
    CSVReader csvReader;
    _rSamples = csvReader.readSamples(_rPaths[_rChoice],SampleType::RESEARCHER);
    _sSamples = csvReader.readSamples(_sPaths[_sChoice],SampleType::SENSOR);
}