#include <Novice.h>
#include <ImGuiManager.h>

const char kWindowTitle[] = "ImGui Test";

bool newFileWnd = 0;
bool exitFlag   = 0;

void ImGuiWindow();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = {0};
    char preKeys[256] = {0};

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ImGuiWindow();

        Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x1f1f1fff, kFillModeSolid);
        Novice::ScreenPrintf(15, 15, "%d", newFileWnd);

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
        if (exitFlag) break;
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}

void ImGuiWindow()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            newFileWnd = ImGui::MenuItem("New File", "Ctrl+Shift+A", nullptr);
            exitFlag = ImGui::MenuItem("Exit", "Esc", nullptr);

            ImGui::EndMenu();
        }

        
        ImGui::EndMainMenuBar();
    }

    if (newFileWnd)
    {
        char inputtext[128]{};
        ImGui::SetNextWindowSize(ImVec2(320, 60));
        ImGui::Begin("Open new file", &newFileWnd, ImGuiWindowFlags_NoResize);

        ImGui::InputText("Path", inputtext, 128);
        ImGui::SameLine();
        ImGui::Button("Load", ImVec2(50, 20));

        ImGui::End();
    }
}
