import pygame
import time
import random

windowWidth = 1300
windowHeight = 700
cellSize = 20
sleepTime = 0


class Labyrinth:
    def __init__(self):
        self.width = windowWidth // cellSize
        self.height = windowHeight // cellSize
        self.numberOfNodes = self.width * self.height
        self.listOfNodes = []
        self.labyrinthNodes = []
        self.prepareLabyrinth()
        pygame.init()
        self.screen = pygame.display.set_mode([windowWidth, windowHeight])
        self.visited = [False] * self.numberOfNodes

    def prepareLabyrinth(self):
        index = 0
        for y in range(self.height):
            for x in range(self.width):
                self.listOfNodes.append([])
                self.labyrinthNodes.append([])
                if x - 1 >= 0:
                    self.listOfNodes[index].append(index - 1)
                if x + 1 < self.width:
                    self.listOfNodes[index].append(index + 1)
                if y - 1 >= 0:
                    self.listOfNodes[index].append(index - self.width)
                if y + 1 < self.height:
                    self.listOfNodes[index].append(index + self.width)
                index += 1

#    def generateLabyrinth(self, index=0, seed=0xABCABCAC):
#        if dispatchEvents():
#            seed = self.seedXORValue ^ rightRotate(seed, 1)
#            self.drawLabyrinth(index)
#            for i in range(len(self.listOfNodes[index])):
#                elIndex = self.listOfNodes[index][(i + seed) % len(self.listOfNodes[index])]
#                found = self.visited[elIndex]
#                if not found:
#                    self.labyrinthNodes[elIndex].append(index)
#                    self.labyrinthNodes[index].append(elIndex)
#                    self.visited[elIndex] = True
#                    self.generateLabyrinth(elIndex, seed)

    def generateLabyrinth(self, index=0, seed=0xABCABCAC):
        stack = [(index, index)]
        random.seed(seed)
        while len(stack) > 0:
            if not dispatchEvents():
                return
            seed = int(random.random() * 100)
            currentIndex, lastIndex = stack.pop(-1)
            if not self.visited[currentIndex]:
                self.visited[currentIndex] = True
                self.labyrinthNodes[lastIndex].append(currentIndex)
                self.labyrinthNodes[currentIndex].append(lastIndex)
                self.drawLabyrinth(currentIndex)
                for i in range(len(self.listOfNodes[currentIndex])):
                    elIndex = self.listOfNodes[currentIndex][(i + seed) % len(self.listOfNodes[currentIndex])]
                    stack.append((elIndex, currentIndex))
        while dispatchEvents():
            continue

    def drawLabyrinth(self, currentIndex):
        self.screen.fill((255, 255, 255))
        index = 0
        for y in range(self.height):
            for x in range(self.width):
                #   left  up    right down
                borderArr = [True, True, True, True]
                self.checkBorders(borderArr, index)
                if currentIndex == index:
                    self.drawCurrentRectangle(x, y, borderArr)
                else:
                    self.drawBorders(x, y, borderArr)
                index += 1

        pygame.display.update()
        time.sleep(sleepTime)

    def checkBorders(self, borderArr, index):
        for edge in self.labyrinthNodes[index]:
            borderIndex = self.edgeToBorderIndex(edge, index)
            if borderIndex != -1:
                borderArr[borderIndex] = False

    def edgeToBorderIndex(self, edge, index):
        if edge == index - 1:
            return 0
        if edge == index + 1:
            return 2
        if edge == index - self.width:
            return 1
        if edge == index + self.width:
            return 3
        return -1

    def drawBorders(self, x, y, borderArray):
        xCoords = [x, x, x + 1, x]
        yCoords = [y, y, y, y + 1]
        widths = [1 / cellSize, 1, 1 / cellSize, 1]
        heights = [1, 1 / cellSize, 1, 1 / cellSize]
        for i in range(4):
            if borderArray[i]:
                pygame.draw.rect(self.screen, (0, 0, 0),
                                 pygame.Rect(xCoords[i] * cellSize,
                                             yCoords[i] * cellSize,
                                             widths[i] * cellSize,
                                             heights[i] * cellSize))

    def drawCurrentRectangle(self, x, y, borderArr):
        pygame.draw.rect(self.screen, (200, 80, 170),
                         pygame.Rect(x * cellSize, y * cellSize, cellSize, cellSize))
        self.drawBorders(x, y, borderArr)


def dispatchEvents():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            return False
    return True


if __name__ == '__main__':
    g = Labyrinth()
    g.generateLabyrinth(0, 0x108A2C7)

