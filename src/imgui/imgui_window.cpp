#include "imgui_window.h"

typedef void (*ImGuiDemoMarkerCallback)(const char* file, int line, const char* section, void* user_data);
extern ImGuiDemoMarkerCallback GImGuiDemoMarkerCallback;
extern void* GImGuiDemoMarkerCallbackUserData;
ImGuiDemoMarkerCallback GImGuiDemoMarkerCallback = NULL;
void* GImGuiDemoMarkerCallbackUserData = NULL;

ImguiWindow::ImguiWindow()
    : m_auto_scroll(true)
{
}

void ImguiWindow::clear()
{
    m_buf.clear();
    m_line_offsets.clear();
    m_line_offsets.push_back(0);
}

void ImguiWindow::add_log(const char* fmt, ...)
{
    int old_size = m_buf.size();
    va_list args;
    va_start(args, fmt);
    m_buf.appendfv(fmt, args);
    va_end(args);
    for (int new_size = m_buf.size(); old_size < new_size; old_size++)
        if (m_buf[old_size] == '\n')
            m_line_offsets.push_back(old_size + 1);
}

void ImguiWindow::imgui_draw(const char* title, bool* p_open)
{
    if (!ImGui::Begin(title, p_open)) {
        ImGui::End();
        return;
    }

    // Options menu
    if (ImGui::BeginPopup("Options")) {
        ImGui::Checkbox("Auto-scroll", &m_auto_scroll);
        ImGui::EndPopup();
    }

    // Main window
    if (ImGui::Button("Options"))
        ImGui::OpenPopup("Options");
    ImGui::SameLine();
    bool clear_logs = ImGui::Button("Clear");
    ImGui::SameLine();
    bool copy = ImGui::Button("Copy");
    ImGui::SameLine();
    m_filter.Draw("Filter", -100.0f);

    ImGui::Separator();

    if (ImGui::BeginChild("scrolling", ImVec2(0, 0), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar)) {
        if (clear_logs)
            clear();
        if (copy)
            ImGui::LogToClipboard();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        const char* buf = m_buf.begin();
        const char* buf_end = m_buf.end();
        if (m_filter.IsActive()) {
            for (int line_no = 0; line_no < m_line_offsets.Size; line_no++) {
                const char* line_start = buf + m_line_offsets[line_no];
                const char* line_end = (line_no + 1 < m_line_offsets.Size) ? (buf + m_line_offsets[line_no + 1] - 1) : buf_end;
                if (m_filter.PassFilter(line_start, line_end))
                    ImGui::TextUnformatted(line_start, line_end);
            }
        } else {
            ImGuiListClipper clipper;
            clipper.Begin(m_line_offsets.Size);
            while (clipper.Step()) {
                for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++) {
                    const char* line_start = buf + m_line_offsets[line_no];
                    const char* line_end = (line_no + 1 < m_line_offsets.Size) ? (buf + m_line_offsets[line_no + 1] - 1) : buf_end;
                    ImGui::TextUnformatted(line_start, line_end);
                }
            }
            clipper.End();
        }
        ImGui::PopStyleVar();

        if (m_auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();
    ImGui::End();
}

void ImguiWindow::set_window(ImGuiIO& io, OpenGLContext& context)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuiDockNodeFlags dockspace_flags = 0 | ImGuiDockNodeFlags_PassthruCentralNode;
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);
    // ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.
    // ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)

    // static int counter = 0;
    // if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
    //     counter++;
    // ImGui::SameLine();
    // ImGui::Text("counter = %d", counter);
    //
    // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    // ImGui::End();
    io.DisplaySize = ImVec2(context.get_window_width(), context.get_window_height());

    glViewport(0, 0, context.get_window_width(), context.get_window_height());
}

void ImguiWindow::draw(bool* p_open)
{
    // static ExampleAppLog log;
    if (!*p_open)
        return;

    // For the demo: add a debug button _BEFORE_ the normal log window contents
    // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
    // Most of the contents of the window will be added by the log.Draw() call.
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Options", p_open);
    IMGUI_DEMO_MARKER("Examples/Log");
    if (ImGui::SmallButton("[Debug] Add 5 entries")) {
        static int counter = 0;
        const char* categories[3] = { "info", "warn", "error" };
        const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
        for (int n = 0; n < 5; n++) {
            const char* category = categories[counter % IM_ARRAYSIZE(categories)];
            const char* word = words[counter % IM_ARRAYSIZE(words)];
            add_log("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
                ImGui::GetFrameCount(), category, ImGui::GetTime(), word);
            counter++;
        }
    }
    ImGui::End();

    // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
    imgui_draw("Options", p_open);
}
