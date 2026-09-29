from fastapi import FastAPI
from fastapi.responses import HTMLResponse
import subprocess
import json

app = FastAPI()


def get_books(sort_type):
    result = subprocess.run(
        ["./books", sort_type],
        capture_output=True,
        text=True
    )

    return json.loads(result.stdout)


@app.get("/books")
def books(sort: str = "title"):
    if sort not in ["title", "price"]:
        sort = "title"

    return get_books(sort)


@app.get("/", response_class=HTMLResponse)
def home():

    return """
    <!DOCTYPE html>
    <html>
    <head>
        <title>Book List</title>

        <style>
            body {
                font-family: Arial;
                max-width: 800px;
                margin: 40px auto;
            }

            button {
                padding: 10px 20px;
                margin-right: 10px;
                cursor: pointer;
            }

            .book {
                border: 1px solid #ddd;
                padding: 15px;
                margin-top: 10px;
                border-radius: 5px;
            }

            .price {
                font-weight: bold;
            }
        </style>
    </head>

    <body>

        <h1>Books</h1>

        <button onclick="loadBooks('title')">
            Alphabetical
        </button>

        <button onclick="loadBooks('price')">
            Price
        </button>

        <div id="books"></div>

        <script>

        async function loadBooks(sort) {

            const response =
                await fetch("/books?sort=" + sort);

            const books =
                await response.json();

            const container =
                document.getElementById("books");

            container.innerHTML = "";

            books.forEach(book => {

                container.innerHTML += `
                    <div class="book">
                        <h3>${book.title}</h3>

                        <p>
                            Author: ${book.author}
                        </p>

                        <p class="price">
                            R$ ${book.price.toFixed(2)}
                        </p>
                    </div>
                `;

            });
        }

        loadBooks("title");

        </script>

    </body>
    </html>
    """