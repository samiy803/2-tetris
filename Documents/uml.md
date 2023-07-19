# UML Diagram for Biquadris

```mermaid
classDiagram
    class Block {
        - start : Position
        - offsets : Position[4]
        + left()
        + right()
        + down()
        + clockwise()
        + counterclockwise()
        + notify()
        %% OBserver pattern for block deletetion
    }
    <<Abstract>> Block
    class IBlock {
      ...
    }
    class JBlock {
        ...
    }
    class LBlock {
        ...       
    }
    class OBlock {
        ...
    }
    class SBlock {
        ...
    }
    class ZBlock {
      ...
    }
    class TBlock {
        ...
    }
    class Player {
        - gameboard: Board
        - factory: BlockFactory
        - effects: Integer
        - level: Integer
        - score: Integer
        + applyBlindEffect()
        + applyForceEffect()
        + applyHeavyEffect()
        + applyVeryHeavyEffect()
    }
    class Board {
        - COLS: Integer
        - ROWS: Integer
        - blocks: Block[*]
        - currentBlock: Block
        - toString(): String
        - drop()
    }
    class Game {
        - player1: Player
        - player2: Player
        - isPlayer1Turn: Boolean
        - windows: Xwindow
        + printGame()
        + runEventLoop()
    }
    class Xwindow {
        - display: Display
        - window: Drawable
        - gc: GC 
        - colours: XColor[*]
        + drawGame(g: Game)
    }

    class BlockFactory {
        + getNextBlock(...): Block
        + SOME_CONST_ABOUT
        + PROBABILITY
    }

    
    
    Block <|-- SBlock
    Block <|-- ZBlock
    Block <|-- IBlock
    Block <|-- JBlock
    Block <|-- LBlock
    Block <|-- OBlock
    Block <|-- TBlock
    Board o-- Block
    BlockFactory ..> Block
    Game --|> Xwindow
    Game --|> Player
    Player --|> Board
    Xwindow ..> Xlib

    class Position {
        + x: Integer
        + y: Integer
    }
```
