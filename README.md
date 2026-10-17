# ICPC Team Notebook

Notebook del team **UPC - Turistas**. Los algoritmos viven en archivos `.cpp` y se insertan directamente en [notebook.tex](notebook.tex); al editar el contenido de un código no hay que duplicar el cambio en LaTeX.

## Generación

Ejecuta:

```bash
python3 build_notebook.py
```

Esto actualiza `notebook.tex` y genera `notebook.pdf` con portada, integrantes, índice y una columna en A4 vertical. El generador usa `pdflatex`; si aún no está instalado, usa LibreOffice como alternativa temporal.

Para la versión libro (A4 horizontal partida en dos columnas, con el contenido corriendo de una columna a la otra) ejecuta:

```bash
python3 build_notebook_book.py
```

Genera `notebook_book.tex` y `notebook_book.pdf`. Sin `pdflatex` usa Chrome/Chromium/Edge; en ese caso instala `pypdf` para que el índice muestre los números de hoja.

En Arch Linux, instala los paquetes necesarios con:

```bash
sudo pacman -S texlive-basic texlive-latex texlive-latexrecommended texlive-latexextra texlive-langspanish
```


| Plataforma | Usuario | Activo desde |
| ---------- | ------- | ------------ |
| Codeforces | [spigi](https://codeforces.com/profile/spigi) | 2022 |
| Codeforces | [Jean_Pool](https://codeforces.com/profile/iAmJP) | 2024 |
| Codeforces | [Santi2007939](https://codeforces.com/profile/Santi2007939) | 2024 |
| Codeforces | [Chatito17](https://codeforces.com/profile/Chatito17) | 2026 |
