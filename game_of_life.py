import time
import pygame
import numpy as np

COLOR_BG = (10, 10, 10)
COLOR_GRID = (40, 40, 40)
COLOR_DIE_NEXT = (170, 170, 170)
COLOR_ALIVE_NEXT = (255, 255, 255)
CELL_SIZE = 15
FPS = 10


def update(screen, cells, size, with_progress=False):
    updated_cells = np.zeros((cells.shape[0], cells.shape[1]))
    padded_cells = np.pad(cells, 1, mode="wrap")

    for row, col in np.ndindex(cells.shape):
        neighbors = padded_cells[row : row + 3, col : col + 3]
        alive = np.sum(neighbors) - padded_cells[row + 1, col + 1]

        color = COLOR_BG if cells[row, col] == 0 else COLOR_ALIVE_NEXT

        if cells[row, col] == 1 and (alive < 2 or alive > 3):
            if alive < 2 or alive > 3:
                if with_progress:
                    color = COLOR_DIE_NEXT
            elif 2 <= alive <= 3:
                updated_cells[row, col] = 1
                if with_progress:
                    color = COLOR_ALIVE_NEXT
        else:
            if alive == 3:
                updated_cells[row, col] = 1
                if with_progress:
                    color = COLOR_ALIVE_NEXT

        pygame.draw.rect(screen, color, (col * size, row * size, size - 1, size - 1))

    return updated_cells


def main() -> None:
    pygame.init()
    pygame.display.set_caption("Game of Life")
    screen = pygame.display.set_mode((800, 800))
    clock = pygame.time.Clock()

    cells = set()
    cells = np.zeros((80, 80))
    screen.fill(COLOR_GRID)
    update(screen, cells, CELL_SIZE)

    pygame.display.flip()
    pygame.display.update()

    running = False

    while True:
        clock.tick(FPS)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                pygame.quit()
                return

            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_g:
                    cells = np.random.choice([0, 1], size=(80, 80), p=[0.7, 0.3])
                    update(screen, cells, CELL_SIZE)
                    pygame.display.update()

                if event.key == pygame.K_SPACE:
                    running = not running
                    update(screen, cells, CELL_SIZE, with_progress=True)
                    pygame.display.update()

                elif event.key == pygame.K_c:
                    cells = np.zeros((80, 80))
                    screen.fill(COLOR_GRID)
                    update(screen, cells, CELL_SIZE)
                    pygame.display.update()

            if pygame.mouse.get_pressed()[0]:
                pos = pygame.mouse.get_pos()

                if cells[pos[1] // CELL_SIZE, pos[0] // CELL_SIZE] == 1:
                    cells[pos[1] // CELL_SIZE, pos[0] // CELL_SIZE] = 0
                else:
                    cells[pos[1] // CELL_SIZE, pos[0] // CELL_SIZE] = 1
                time.sleep(0.1)
                update(screen, cells, CELL_SIZE)
                pygame.display.update()

        if running:
            cells = update(screen, cells, CELL_SIZE)
            pygame.display.update()

    pygame.quit()


if __name__ == "__main__":
    main()
