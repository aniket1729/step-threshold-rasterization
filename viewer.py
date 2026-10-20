
import subprocess
import sys
import pygame

WIDTH, HEIGHT = 640, 480
SCALE = 2

BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
YELLOW = (255, 255, 0)
LIGHTGREEN = (144, 238, 144)
GRAY = (200, 200, 200)

COLORS = {
    0: WHITE,
    1: YELLOW,
    2: LIGHTGREEN,
}


def main():
    # Run the C++ program and capture its drawing commands.
    try:
        result = subprocess.run(
            ["./cg_lines"],
            capture_output=True,
            text=True,
            check=True,
        )
    except Exception as exc:
        print(f"Error running C++ program: {exc}")
        return

    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("CG Lines - Step-Threshold Algorithm")

    font = pygame.font.Font(None, 22)
    screen.fill(BLACK)

    for raw_line in result.stdout.splitlines():
        # Split only twice so the full message is preserved.
        parts = raw_line.split(maxsplit=2)

        if not parts:
            continue

        command = parts[0]

        if command == "CLEAR":
            screen.fill(BLACK)

        elif command == "P" and len(parts) == 3:
            # Pixel commands: P x y color
            values = raw_line.split()
            if len(values) != 4:
                continue

            _, x, y, color = values
            x, y, color = int(x), int(y), int(color)

            px, py = x * SCALE, y * SCALE

            if 0 <= px < WIDTH and 0 <= py < HEIGHT:
                pygame.draw.rect(
                    screen,
                    COLORS.get(color, WHITE),
                    (px, py, SCALE, SCALE),
                )

        elif command == "T" and len(parts) == 3:
            # Text commands: T y message
            y = int(parts[1])
            message = parts[2]

            label = font.render(message, True, GRAY)
            screen.blit(label, (20, y))

        elif command == "END":
            continue

    pygame.display.flip()

    # Keep the window open until the user closes it.
    running = True
    clock = pygame.time.Clock()

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False

        clock.tick(30)

    pygame.quit()
    sys.exit()


if __name__ == "__main__":
    main()
