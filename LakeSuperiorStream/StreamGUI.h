#pragma once

#include "imGUIHeader.h"
#include "Stream.h"
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <filesystem>
#include <iostream>

#include "CSVReader.h"

/**
 * @class GUI
 * @brief Graphical User Interface wrapper class that encapsulates much of the
 * details needed to use the imGUI user interface toolkit.
 *
 * This class hides some of the functions and variables needed to
 * create a user interface with imGUI. To use it, you need to
 * construct a GUI instance, and then call the mainLoop function.
 */
class GUI
{
public:
    /**
     * Base constructor for GUI
     *
     */
    GUI();
    virtual ~GUI();

    /**
     * Change the background color of the GUI, which is specified with RGB color values.  See https://rgbcolorpicker.com/0-1 for some
     * way to see how these colors are formed.
     *
     * @param red float that specifies the red component. Value is in the range of 0.0f to 1.0f, with 0.0 being no red and 1.0 being all red
     * @param green float that specifies the greend component. Value is in the range of 0.0f to 1.0f, with 0.0 being no green and 1.0 being all green
     * @param blue float that specifies the blued component. Value is in the range of 0.0f to 1.0f, with 0.0 being no blue and 1.0 being all blue
     * @return Nothing returned.
     */
    void setBackgroundColor(float red, float green, float blue);

    /**
     * The bulk of the code for rendering various GUI elements, such as
     * buttons, input text boxes and other items. The mainLoop function
     * does not return unless the GUI window is closed.
     *
     * @return Nothing returned.
     */
    void mainLoop();

private:
    // Variable that holds a pointer to the underlying window toolkit
    // implementation.
    GLFWwindow* m_window;

    // You can change the clear color
    ImVec4 m_clear_color;

    //csv reader
    CSVReader imGUI_CSVreader;

    static constexpr std::string_view m_windowTitle{ "imGUI Example" };


    /**
     * find the test data folder in the project directory
     * @return path to the test data
     */
    static std::filesystem::path _findTestDataDir();
    /**
     * Sets up the directory arrays
     */
    void _setDirectoryArrays();

    //Researcher paths, filenames, filecount, current drop down choice, and samples
    char** _rPaths;
    char** _rNames;
    int _rPathCount;
    int _rChoice = 1;
    std::vector<std::shared_ptr<ISample>> _rSamples;

    //Researcher paths, filenames, filecount, current drop down choice, and samples
    char** _sPaths;
    char** _sNames;
    int _sPathCount;
    int _sChoice = 0;
    std::vector<std::shared_ptr<ISample>> _sSamples;

    /**
     * Lists out the files in a directory
     * @param directory to search through
     * @param pathCount number of files found
     * @param names of files found in directory
     * @return the file paths
     */
    static char **listFilesInDirectory(const std::filesystem::path &directory, int &pathCount, char** &names);
    //if it should show the input window
    bool _showInputWindow = true;
    /**
     * draw to the frame
     */
    void renderFrame();
    /**
     * render the file choosing part
     */
    void renderFileChooser();
    /**
     * render the statistics part
     */
    void renderStatistics();
    /**
     * set up the frame before drawing to it
     */
    static void setUpFrame();
    /**
     * read in the files
     */
    void readFiles();

    //date input field
    char dateInput[99] = "4/18/07";

    //Current stream object
    Stream stream;
    //Current date object
    Time date;
};