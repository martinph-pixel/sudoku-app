from fastapi import FastAPI, Query
from fastapi.middleware.cors import CORSMiddleware
import numpy as np
import sudoku

app = FastAPI()

origins = [
    "http://localhost.tiangolo.com",
    "https://localhost.tiangolo.com",
    "http://localhost",
    "http://localhost:3000",
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)


@app.get("/ping")
async def ping():
    return {"status": "OK"}


@app.get("/board")
async def board(
    size: int = Query(..., ge=2), percent_filled: float = Query(..., ge=0.0, le=100.0)
):
    flat = sudoku.generate_random_board(size, percent_filled)
    N = size * size

    return np.array(flat).reshape((N, N)).tolist()
