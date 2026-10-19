""" pra executar: 
    uvicorn main:app --reload"""
from fastapi import FastAPI
from fastapi.responses import HTMLResponse
import subprocess
import json
from pathlib import Path

app = FastAPI()

# Directory containing this Python file
BASE_DIR = Path(__file__).resolve().parent

# C executable
BOOKS_PROGRAM = BASE_DIR / "books"


def get_books(sort_type):
    result = subprocess.run(
        [str(BOOKS_PROGRAM), str(sort_type)],
        capture_output=True,
        text=True
    )

    # C program returned an error
    if result.returncode != 0:
        print("C PROGRAM ERROR:")
        print(result.stdout)
        print(result.stderr)

        raise RuntimeError("C program failed")

    # Convert C JSON output into Python objects
    return json.loads(result.stdout)


@app.get("/books")
def books(sort: int = 2):

    # 0 = price ascending
    # 1 = price descending
    # 2 = name ascending
    # 3 = name descending

    if sort not in [0, 1, 2, 3]:
        sort = 2

    return get_books(sort)


@app.get("/", response_class=HTMLResponse)
@app.get("/", response_class=HTMLResponse)
def home():
    return """
    <!DOCTYPE html>
    <html lang="pt-BR">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">

        <title>Minha Biblioteca</title>

        <style>
            @import url('https://fonts.googleapis.com/css2?family=DM+Sans:wght@400;500;600;700&family=Playfair+Display:wght@600;700&display=swap');

            * {
                box-sizing: border-box;
                margin: 0;
                padding: 0;
            }

            body {
                font-family: 'DM Sans', sans-serif;

                background:
                    radial-gradient(
                        circle at 80% 0%,
                        rgba(91, 126, 103, 0.10),
                        transparent 32%
                    ),
                    #111412;

                color: #eeeae2;
                min-height: 100vh;
            }


            /* =========================
               NAVEGAÇÃO
            ========================= */

            nav {
                height: 78px;

                display: flex;
                align-items: center;
                justify-content: space-between;

                max-width: 1180px;
                margin: auto;
                padding: 0 30px;

                border-bottom: 1px solid rgba(255,255,255,0.055);
            }

            .logo {
                font-size: 21px;
                font-weight: 700;
                letter-spacing: -0.6px;
                color: #eeeae2;
            }

            .logo span {
                color: #83a88e;
            }

            .nav-right {
                display: flex;
                gap: 30px;
                align-items: center;
            }

            .nav-link {
                color: #858d88;
                font-size: 14px;
                text-decoration: none;

                transition: color 0.2s ease;
            }

            .nav-link:hover {
                color: #e7e9e5;
            }


            /* =========================
               HERO
            ========================= */

            .hero {
                max-width: 1180px;
                margin: 75px auto 65px;
                padding: 0 30px;
            }

            .eyebrow {
                text-transform: uppercase;
                letter-spacing: 2.5px;

                font-size: 10px;
                font-weight: 700;

                color: #83a88e;

                margin-bottom: 18px;
            }

            .hero h1 {
                font-family: 'Playfair Display', serif;

                font-size: clamp(44px, 6vw, 72px);
                line-height: 1.02;

                letter-spacing: -2.5px;

                max-width: 750px;
                font-weight: 700;

                color: #f0ede6;
            }

            .hero p {
                margin-top: 24px;

                color: #858d88;

                font-size: 16px;
                line-height: 1.7;

                max-width: 570px;
            }


            /* =========================
               BIBLIOTECA
            ========================= */

            .library {
                max-width: 1180px;
                margin: auto;
                padding: 0 30px 80px;
            }

            .library-header {
                display: flex;
                justify-content: space-between;
                align-items: center;

                margin-bottom: 22px;
            }

            .library-title {
                font-size: 11px;
                font-weight: 700;

                letter-spacing: 1.8px;

                color: #aeb5b0;
            }

            .book-count {
                color: #606964;
                font-size: 13px;
            }


            /* =========================
               FILTROS
            ========================= */

            .sort-container {
                display: flex;
                gap: 8px;

                margin-bottom: 25px;

                flex-wrap: wrap;
            }

            .sort-button {
                border: 1px solid #303733;

                background: #171b19;
                color: #8e9791;

                padding: 10px 17px;

                border-radius: 100px;

                font-family: inherit;
                font-size: 13px;
                font-weight: 500;

                cursor: pointer;

                transition:
                    background 0.2s ease,
                    border 0.2s ease,
                    color 0.2s ease,
                    transform 0.15s ease;
            }

            .sort-button:hover {
                background: #1d2420;
                border-color: #46534b;
                color: #dce1dd;
            }

            .sort-button:active {
                transform: scale(0.97);
            }

            .sort-button.active {
                background: #779982;
                color: #101411;

                border-color: #779982;

                font-weight: 700;
            }


            /* =========================
               LIVROS
            ========================= */

            #books {
                display: grid;

                grid-template-columns:
                    repeat(auto-fill, minmax(250px, 1fr));

                gap: 14px;
            }

            .book {
                background:
                    linear-gradient(
                        145deg,
                        #1a1f1c,
                        #161a18
                    );

                border: 1px solid #282e2a;

                border-radius: 18px;

                padding: 25px;

                min-height: 190px;

                display: flex;
                flex-direction: column;
                justify-content: space-between;

                transition:
                    transform 0.25s ease,
                    border-color 0.25s ease,
                    box-shadow 0.25s ease;
            }

            .book:hover {
                transform: translateY(-5px);

                border-color: #435047;

                box-shadow:
                    0 18px 40px rgba(0,0,0,0.30);
            }

            .book-number {
                color: #58615c;

                font-size: 11px;
                font-weight: 600;

                letter-spacing: 1px;

                margin-bottom: 18px;
            }

            .book h3 {
                font-family: 'Playfair Display', serif;

                font-size: 22px;
                line-height: 1.25;

                font-weight: 600;

                color: #e7e4dd;
            }

            .book-bottom {
                display: flex;

                align-items: center;
                justify-content: space-between;

                margin-top: 30px;
            }

            .price {
                font-size: 14px;

                font-weight: 700;

                color: #83a88e;
            }

            .book-dot {
                width: 7px;
                height: 7px;

                border-radius: 50%;

                background: #779982;

                box-shadow:
                    0 0 12px rgba(119,153,130,0.35);
            }


            /* =========================
               FOOTER
            ========================= */

            footer {
                max-width: 1180px;
                margin: auto;

                padding: 25px 30px 45px;

                border-top: 1px solid #252b27;

                color: #555d58;

                font-size: 12px;
            }


            /* =========================
               MOBILE
            ========================= */

            @media (max-width: 650px) {

                nav {
                    padding: 0 20px;
                }

                .nav-right {
                    display: none;
                }

                .hero {
                    margin-top: 50px;
                    padding: 0 20px;
                }

                .hero h1 {
                    font-size: 45px;
                }

                .library {
                    padding: 0 20px 55px;
                }

                #books {
                    grid-template-columns: 1fr;
                }

                .library-header {
                    align-items: flex-start;

                    gap: 8px;

                    flex-direction: column;
                }
            }

        </style>
    </head>


    <body>

        <!-- NAVEGAÇÃO -->

        <nav>

            <div class="logo">
                minha<span>biblioteca</span>
            </div>

            <div class="nav-right">

                <a class="nav-link" href="#">
                    Biblioteca
                </a>

                <a class="nav-link" href="#">
                    Sobre
                </a>

            </div>

        </nav>


        <!-- HERO -->

        <section class="hero">

            <div class="eyebrow">
                Coleção pessoal
            </div>

            <h1>
                Livros que<br>
                valem lembrar.
            </h1>

            <p>
                Uma coleção pessoal organizada de forma simples,
                elegante e exatamente do jeito que você quiser.
            </p>

        </section>


        <!-- BIBLIOTECA -->

        <main class="library">

            <div class="library-header">

                <div class="library-title">
                    SUA COLEÇÃO
                </div>

                <div
                    class="book-count"
                    id="book-count">

                    Carregando...

                </div>

            </div>


            <!-- ORDENAÇÃO -->

            <div class="sort-container">

                <button
                    class="sort-button active"
                    onclick="loadBooks(2, this)">

                    Nome ↑

                </button>

                <button
                    class="sort-button"
                    onclick="loadBooks(3, this)">

                    Nome ↓

                </button>

                <button
                    class="sort-button"
                    onclick="loadBooks(0, this)">

                    Preço ↑

                </button>

                <button
                    class="sort-button"
                    onclick="loadBooks(1, this)">

                    Preço ↓

                </button>

            </div>


            <!-- LIVROS -->

            <div id="books"></div>

        </main>


        <!-- RODAPÉ -->

        <footer>

            Minha Biblioteca · Desenvolvido com C + FastAPI

        </footer>


        <script>

            async function loadBooks(sort, button) {

                try {

                    const response =
                        await fetch(
                            "/books?sort=" + sort
                        );

                    if (!response.ok) {

                        throw new Error(
                            "Erro HTTP: " +
                            response.status
                        );

                    }

                    const books =
                        await response.json();


                    const container =
                        document.getElementById(
                            "books"
                        );

                    const count =
                        document.getElementById(
                            "book-count"
                        );


                    container.innerHTML = "";


                    count.innerText =
                        books.length +
                        (
                            books.length === 1
                            ? " livro"
                            : " livros"
                        );


                    /* Botão ativo */

                    document
                        .querySelectorAll(
                            ".sort-button"
                        )
                        .forEach(btn => {

                            btn.classList.remove(
                                "active"
                            );

                        });


                    if (button) {

                        button.classList.add(
                            "active"
                        );

                    }


                    /* Criar cartões */

                    books.forEach(
                        (book, index) => {

                            const element =
                                document.createElement(
                                    "div"
                                );

                            element.className =
                                "book";


                            element.innerHTML = `

                                <div>

                                    <div class="book-number">

                                        ${String(index + 1)
                                            .padStart(2, "0")}

                                    </div>

                                    <h3>
                                        ${book.nome}
                                    </h3>

                                </div>


                                <div class="book-bottom">

                                    <div class="price">

                                        R$ ${(book.preco / 100)
                                            .toFixed(2)
                                            .replace(".", ",")}

                                    </div>

                                    <div class="book-dot"></div>

                                </div>

                            `;


                            container.appendChild(
                                element
                            );

                        }
                    );

                }

                catch (error) {

                    console.error(
                        "Erro ao carregar livros:",
                        error
                    );

                }

            }


            /* Carregamento inicial */

            loadBooks(2);

        </script>

    </body>
    </html>
    """
