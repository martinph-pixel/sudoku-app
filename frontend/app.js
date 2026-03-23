const BOX_SIZE = 3;
const SIZE = BOX_SIZE * BOX_SIZE;

function createEmptyGrid(size) {
    const grid = Array(size);
    for (let r = 0; r < size; r++) {
        grid[r] = Array(size);
        for (let c = 0; c < size; c++) {
            grid[r][c] = 0;
        }
    }
    return grid;
}

function renderBoard(grid, boxSz, selectedRow, selectedCol, cellClickedCB) {
    const board = document.createElement("div");
    board.className = "board";
    board.style.setProperty("--box-size", boxSz);

    const size = boxSz * boxSz;

    for (let i = 0; i < size; i++) {
        const box = document.createElement("div");
        box.className = "box";

        for (let j = 0; j < size; j++) {
            const cell = document.createElement("div");
            cell.className = "cell";

            const col = ((i % boxSz) * boxSz) + (j % boxSz);
            const row = Math.floor(i / boxSz) * boxSz + Math.floor(j / boxSz);

            const value = grid[row][col];
            cell.textContent = value === 0 ? "" : String(value);

            if (row === selectedRow && col === selectedCol) {
                cell.classList.add("selected");
            }

            cell.addEventListener("click", () => {
                cellClickedCB(row, col);
            });

            box.appendChild(cell);
        }

        board.appendChild(box);
    }

    return board;
}

function main() {
    const app = document.getElementById("app");
    const grid = createEmptyGrid(SIZE);

    let selectedRow = null;
    let selectedCol = null;
    let inputBuffer = "";

    function selectCell(row, col) {
        selectedRow = row;
        selectedCol = col;
        inputBuffer = "";
        render();
    }

    function commitBuffer() {
        if (selectedRow === null || selectedCol === null) {
            return;
        }

        const value = inputBuffer === "" ? 0 : Number(inputBuffer);
        grid[selectedRow][selectedCol] = value;
    }

    function render() {
        const board = renderBoard(
            grid,
            BOX_SIZE,
            selectedRow,
            selectedCol,
            selectCell
        );

        app.replaceChildren(board);
    }

    document.addEventListener("keydown", (event) => {
        if (selectedRow === null || selectedCol === null) {
            return;
        }

        if (event.key >= "0" && event.key <= "9") {
            const nextBuffer = inputBuffer + event.key;
            const nextValue = Number(nextBuffer);

            if (nextValue <= SIZE) {
                inputBuffer = nextBuffer;
                commitBuffer();
                render();
            }
            return;
        }

        if (event.key === "Backspace") {
            inputBuffer = inputBuffer.slice(0, -1);
            commitBuffer();
            render();
            return;
        }

        if (event.key === "Delete") {
            inputBuffer = "";
            commitBuffer();
            render();
            return;
        }

        if (event.key === "Escape") {
            inputBuffer = "";
            render();
        }
    });

    render();
}

main();