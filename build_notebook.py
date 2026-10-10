#!/usr/bin/env python3
"""Build the La Tasita LaTeX source and PDF from the C++ snippets."""

from pathlib import Path
from html import escape
import re
import shutil
import subprocess
import tempfile


ROOT = Path(__file__).resolve().parent
TEAM = "UPC - Turistas"
MEMBERS = ["spigi", "Jean_Pool", "Santi2007939", "Chatito17"]
SKIP = {"template.cpp", "otros/plantilla.cpp"}


def code_files():
    return sorted(
        (p for p in ROOT.rglob("*.cpp") if p.relative_to(ROOT).as_posix() not in SKIP),
        key=lambda p: (p.parent.as_posix(), p.name.lower()),
    )


def title(path):
    name = re.sub(r"(?<=[a-z0-9])(?=[A-Z])", " ", path.stem)
    name = name.replace("-", " ").replace("_", " ").title()
    for short, full in {"Dsu": "DSU", "Hld": "HLD", "Lcs": "LCS", "Lis": "LIS",
                        "Ntt": "NTT", "Fft": "FFT", "Kmp": "KMP"}.items():
        name = re.sub(rf"\b{short}\b", full, name)
    return name.replace("2 Sat", "2-SAT")


def category_title(folder):
    return {"DP": "Dynamic Programming", "data-structures": "Data Structures"}.get(
        folder, folder.replace("-", " ").title())


def latex_escape(value):
    for char, repl in [("\\", r"\textbackslash{}"), ("&", r"\&"), ("%", r"\%"),
                       ("$", r"\$"), ("#", r"\#"), ("_", r"\_"),
                       ("{", r"\{"), ("}", r"\}"), ("~", r"\textasciitilde{}"),
                       ("^", r"\textasciicircum{}")]:
        value = value.replace(char, repl)
    return value


def build_tex(files):
    lines = [r"\documentclass[a4paper,10pt]{article}",
             r"\usepackage[utf8]{inputenc}", r"\usepackage[T1]{fontenc}",
             r"\usepackage[spanish]{babel}", r"\usepackage[margin=1.6cm]{geometry}",
             r"\usepackage{xcolor}", r"\usepackage{listings}", r"\usepackage{hyperref}",
             r"\usepackage{titlesec}", r"\definecolor{codebg}{RGB}{248,249,251}",
             r"\lstset{language=C++,basicstyle=\ttfamily\fontsize{8}{9}\selectfont,",
             r"  keywordstyle=\color{blue!65!black},commentstyle=\color{green!35!black},",
             r"  stringstyle=\color{red!55!black},backgroundcolor=\color{codebg},",
             r"  numbers=left,numberstyle=\tiny\color{gray},numbersep=4pt,",
             r"  breaklines=true,breakatwhitespace=false,keepspaces=true,",
             r"  showstringspaces=false,tabsize=2,aboveskip=3pt,belowskip=6pt,",
             r"  literate={á}{{\'a}}1 {é}{{\'e}}1 {í}{{\'i}}1 {ó}{{\'o}}1 {ñ}{{\~n}}1 {—}{---}1 {─}{-}1}",
             r"\titleformat{\section}{\Large\bfseries\color{blue!55!black}}{}{0em}{}",
             r"\titleformat{\subsection}{\large\bfseries}{}{0em}{}",
             r"\setlength{\parindent}{0pt}", r"\begin{document}",
             r"\pagenumbering{roman}",
             r"\begin{titlepage}\centering\vspace*{2cm}",
             r"{\Huge\bfseries Notebook ICPC\\[0.4cm]La Tasita\par}",
             r"\vspace{1cm}{\LARGE Team: " + latex_escape(TEAM) + r"\par}",
             r"\vfill{\Large Integrantes\par}\vspace{0.4cm}",
             (r"\\" + "\n").join(latex_escape(m) for m in MEMBERS),
             r"\vfill{\large Competitive Programming Notebook\par}\end{titlepage}",
             r"\pagenumbering{arabic}", r"\tableofcontents", r"\clearpage"]
    active = None
    for path in files:
        rel = path.relative_to(ROOT).as_posix()
        category = path.parent.name
        if category != active:
            active = category
            lines.append(r"\section{" + latex_escape(category_title(category)) + "}")
        lines.extend([r"\subsection{" + latex_escape(title(path)) + "}",
                      r"\lstinputlisting{" + rel + "}"])
    lines.append(r"\end{document}")
    (ROOT / "notebook.tex").write_text("\n".join(lines) + "\n", encoding="utf-8")


def build_html_pdf(files, soffice):
    groups = {}
    for path in files:
        groups.setdefault(path.parent.name, []).append((title(path), path))
    toc = "".join(
        f'<h2>{escape(category_title(category))}</h2><ul>'
        + "".join(f"<li>{escape(name)}</li>" for name, _ in entries)
        + "</ul>"
        for category, entries in groups.items()
    )
    sections = []
    for category, entries in groups.items():
        sections.append(f'<h1>{escape(category_title(category))}</h1>')
        for name, path in entries:
            code = escape(path.read_text(encoding="utf-8"))
            sections.append(f'<h2>{escape(name)}</h2><pre>{code}</pre>')
    members = "<br>".join(escape(member) for member in MEMBERS)
    html = f'''<!doctype html><html><head><meta charset="utf-8"><style>
@page {{ size: A4 portrait; margin: 15mm; }}
body {{ font-family: Arial, sans-serif; color:#172033; }}
.cover {{ height:245mm; page-break-after:always; text-align:center; padding-top:45mm; box-sizing:border-box; }}
.newpage {{ page-break-before:always; }}
h1 {{ font-size:18pt; color:#2456a6; border-bottom:1px solid #2456a6; padding-bottom:4pt; }}
h2 {{ font-size:12pt; margin:12pt 0 4pt; }}
pre {{ white-space:pre-wrap; overflow-wrap:anywhere; font:8pt/1.15 "Liberation Mono",monospace;
  background:#f8f9fb; padding:5pt; }}
</style></head><body>
<section class="cover"><h1 style="font-size:30pt;border:0">Notebook ICPC<br>La Tasita</h1>
<h2 style="font-size:20pt">Team: {escape(TEAM)}</h2><h2>Integrantes</h2>{members}</section>
<div class="newpage"></div><h1>Índice</h1>{toc}
<div class="newpage"></div>{''.join(sections)}</body></html>'''
    with tempfile.TemporaryDirectory(prefix="la-tasita-") as tmp:
        tmp = Path(tmp)
        source = tmp / "notebook.html"
        source.write_text(html, encoding="utf-8")
        profile = (tmp / "lo-profile").as_uri()
        subprocess.run([soffice, "--headless", f"-env:UserInstallation={profile}",
                        "--convert-to", "pdf", "--outdir", str(ROOT), str(source)],
                       check=True, capture_output=True, text=True)


def main():
    files = code_files()
    build_tex(files)
    pdflatex = shutil.which("pdflatex")
    if not pdflatex:
        soffice = shutil.which("soffice")
        if not soffice:
            raise SystemExit("No se encontró pdflatex ni LibreOffice para generar notebook.pdf")
        build_html_pdf(files, soffice)
        print(f"Generados notebook.tex y notebook.pdf en A4 vertical con {len(files)} códigos.")
        print("Aviso: el PDF se hizo con LibreOffice porque pdflatex no está instalado.")
        return
    command = [pdflatex, "-interaction=nonstopmode", "-halt-on-error", "notebook.tex"]
    for _ in range(2):
        result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True,
                                 encoding="utf-8", errors="replace")
        if result.returncode:
            raise SystemExit(result.stdout[-4000:] + result.stderr[-1000:])
    print(f"Generados notebook.tex y notebook.pdf con pdflatex en A4 vertical ({len(files)} códigos).")


if __name__ == "__main__":
    main()
