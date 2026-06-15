#include <3ds.h>
#include <citro2d.h>
#include "enemy.h"

struct Player {
    float x;
    float y;
    float velY;
    bool grounded;
};

int main(int argc, char* argv[]) {
    gfxInitDefault();

    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    C3D_RenderTarget* top =
        C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

    Player player;

    player.x = 50.0f;
    player.y = 180.0f;
    player.velY = 0.0f;
    player.grounded = true;

    Enemy enemy(250.0f, 200.0f);

    const float gravity = 0.35f;
    const float jumpForce = -6.5f;
    const float moveSpeed = 2.5f;
    const float groundY = 200.0f;

    while (aptMainLoop()) {

        hidScanInput();

        u32 kDown = hidKeysDown();
        u32 kHeld = hidKeysHeld();

        if (kDown & KEY_START)
            break;

        circlePosition circle;
        hidCircleRead(&circle);

        // Movimento
        if (circle.dx < -20 || (kHeld & KEY_LEFT))
            player.x -= moveSpeed;

        if (circle.dx > 20 || (kHeld & KEY_RIGHT))
            player.x += moveSpeed;

        // Pulo
        if ((kDown & KEY_A) && player.grounded) {
            player.velY = jumpForce;
            player.grounded = false;
        }

        // Gravidade
        player.velY += gravity;
        player.y += player.velY;

        // Chão
        if (player.y >= groundY) {
            player.y = groundY;
            player.velY = 0;
            player.grounded = true;
        }

        // Limites da tela
        if (player.x < 0)
            player.x = 0;

        if (player.x > 380)
            player.x = 380;

        // Atualizar inimigo
        enemy.Update();

        // Colisão simples
        bool collision =
            player.x + 20 > enemy.x &&
            player.x < enemy.x + 20 &&
            player.y + 20 > enemy.y &&
            player.y < enemy.y + 20;

        if (collision) {
            player.x = 50;
            player.y = 180;
            player.velY = 0;
        }

        // Render
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

        C2D_TargetClear(top, C2D_Color32(100, 180, 255, 255));
        C2D_SceneBegin(top);

        // Chão
        C2D_DrawRectSolid(
            0, 220, 0,
            400, 20,
            C2D_Color32(80, 180, 80, 255)
        );

        // Jogador
        C2D_DrawRectSolid(
            player.x,
            player.y,
            0,
            20, 20,
            C2D_Color32(255, 0, 0, 255)
        );

        // Inimigo
        enemy.Draw();

        C3D_FrameEnd(0);
    }

    C2D_Fini();
    C3D_Fini();
    gfxExit();

    return 0;
}
