#!/usr/bin/env python3
"""Build the La Tasita notebook as a book: A4 landscape split in two columns."""

from pathlib import Path
from html import escape
import re
import shutil
import subprocess
import tempfile

from build_notebook import (ROOT, TEAM, MEMBERS, code_files, title,
                            category_title, latex_escape)


JOB = "notebook_book"
MARK = "QQPAGEMARKQQ"
BROWSERS = ["chromium", "chromium-browser", "google-chrome", "chrome", "msedge",
            r"C:\Program Files\Google\Chrome\Application\chrome.exe",
            r"C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe",
            r"C:\Program Files\Microsoft\Edge\Application\msedge.exe"]


def build_tex(files):
    lines = [r"\documentclass[a4paper,landscape,10pt]{article}",
             r"\usepackage[utf8]{inputenc}", r"\usepackage[T1]{fontenc}",
             r"\usepackage[spanish]{babel}",
             r"\usepackage[landscape,margin=1cm,top=1.2cm,bottom=1.2cm]{geometry}",
             r"\usepackage{multicol}", r"\usepackage{xcolor}", r"\usepackage{listings}",
             r"\usepackage{hyperref}", r"\usepackage{titlesec}",
             r"\definecolor{codebg}{RGB}{248,249,251}",
             r"\setlength{\columnsep}{0.9cm}", r"\setlength{\columnseprule}{0.4pt}",
             r"\lstset{language=C++,basicstyle=\ttfamily\fontsize{7}{8}\selectfont,",
             r"  keywordstyle=\color{blue!65!black},commentstyle=\color{green!35!black},",
             r"  stringstyle=\color{red!55!black},backgroundcolor=\color{codebg},",
             r"  numbers=left,numberstyle=\tiny\color{gray},numbersep=3pt,xleftmargin=8pt,",
             r"  breaklines=true,breakatwhitespace=false,keepspaces=true,",
             r"  showstringspaces=false,tabsize=2,aboveskip=2pt,belowskip=4pt,",
             r"  literate={á}{{\'a}}1 {é}{{\'e}}1 {í}{{\'i}}1 {ó}{{\'o}}1 {ñ}{{\~n}}1 {—}{---}1 {─}{-}1}",
             r"\titleformat{\section}{\large\bfseries\color{blue!55!black}}{}{0em}{}",
             r"\titleformat{\subsection}{\normalsize\bfseries}{}{0em}{}",
             r"\titlespacing*{\section}{0pt}{6pt}{3pt}",
             r"\titlespacing*{\subsection}{0pt}{4pt}{1pt}",
             r"\setlength{\parindent}{0pt}", r"\begin{document}",
             r"\pagenumbering{roman}",
             r"\begin{titlepage}\centering\vspace*{1.5cm}",
             r"{\Huge\bfseries Notebook ICPC\\[0.4cm]La Tasita\par}",
             r"\vspace{0.8cm}{\LARGE Team: " + latex_escape(TEAM) + r"\par}",
             r"\vfill{\Large Integrantes\par}\vspace{0.4cm}",
             (r"\\" + "\n").join(latex_escape(m) for m in MEMBERS),
             r"\vfill{\large Competitive Programming Notebook\par}\end{titlepage}",
             r"\pagenumbering{arabic}", r"\begin{multicols*}{2}",
             r"\tableofcontents", r"\columnbreak"]
    active = None
    for path in files:
        rel = path.relative_to(ROOT).as_posix()
        category = path.parent.name
        if category != active:
            active = category
            lines.append(r"\section{" + latex_escape(category_title(category)) + "}")
        lines.extend([r"\subsection{" + latex_escape(title(path)) + "}",
                      r"\lstinputlisting{" + rel + "}"])
    lines.extend([r"\end{multicols*}", r"\end{document}"])
    (ROOT / f"{JOB}.tex").write_text("\n".join(lines) + "\n", encoding="utf-8")


def build_html(files, pages=None):
    """With pages=None, mark each heading so its page can be found in the PDF."""
    groups = {}
    for path in files:
        groups.setdefault(path.parent.name, []).append((title(path), path))
    entries_html, sections, index = [], [], 0
    for category, entries in groups.items():
        entries_html.append(f'<h3>{escape(category_title(category))}</h3><ul>')
        sections.append(f'<h1>{escape(category_title(category))}</h1>')
        for name, path in entries:
            page = pages[index] if pages else ""
            mark = "" if pages else f'<span class="mark">{MARK}{index}{MARK}</span>'
            entries_html.append(f'<li><span>{escape(name)}</span><b>{page}</b></li>')
            code = escape(path.read_text(encoding="utf-8"))
            sections.append(f'<h2>{escape(name)}{mark}</h2><pre>{code}</pre>')
            index += 1
        entries_html.append("</ul>")
    toc = "".join(entries_html)
    members = "<br>".join(escape(member) for member in MEMBERS)
    return f'''<!doctype html><html><head><meta charset="utf-8"><style>
@page {{ size: A4 landscape; margin: 10mm 10mm 12mm;
  @bottom-center {{ content: counter(page); font: 9pt Arial, sans-serif; color:#55607a; }} }}
@page :first {{ @bottom-center {{ content: none; }} }}
body {{ margin:0; font-family: Arial, sans-serif; color:#172033; }}
.mark {{ font-size:1px; color:#fff; }}
.toc li {{ display:flex; align-items:baseline; }}
.toc li span {{ flex:none; }}
.toc li::after {{ content:""; flex:1; order:1; border-bottom:1px dotted #9aa3b2; margin:0 4pt; }}
.toc li b {{ order:2; font-weight:normal; }}
.cover {{ height:185mm; break-after:page; text-align:center; padding-top:30mm; box-sizing:border-box; }}
.book {{ column-count:2; column-gap:9mm; column-rule:0.5pt solid #9aa3b2; column-fill:auto; }}
.toc {{ break-after:column; }}
.toc ul {{ margin:0 0 4pt; padding-left:14pt; font-size:9pt; }}
h1 {{ font-size:13pt; color:#2456a6; border-bottom:1px solid #2456a6; padding-bottom:2pt; margin:6pt 0 3pt; }}
h2 {{ font-size:10pt; margin:6pt 0 2pt; break-after:avoid; }}
h3 {{ font-size:10pt; margin:5pt 0 1pt; color:#2456a6; }}
pre {{ margin:0 0 4pt; white-space:pre-wrap; overflow-wrap:anywhere; font:7pt/1.15 "Liberation Mono",Consolas,monospace;
  background:#f8f9fb; padding:3pt; }}
</style></head><body>
<section class="cover"><h1 style="font-size:30pt;border:0">Notebook ICPC<br>La Tasita</h1>
<h2 style="font-size:20pt">Team: {escape(TEAM)}</h2><h2>Integrantes</h2>{members}</section>
<div class="book"><div class="toc"><h1>Índice</h1>{toc}</div>{''.join(sections)}</div></body></html>'''


def print_pdf(html, browser, output):
    with tempfile.TemporaryDirectory(prefix="la-tasita-") as tmp:
        tmp = Path(tmp)
        source = tmp / f"{JOB}.html"
        source.write_text(html, encoding="utf-8")
        subprocess.run([browser, "--headless", "--disable-gpu", "--no-pdf-header-footer",
                        f"--user-data-dir={tmp / 'profile'}",
                        f"--print-to-pdf={output}", source.as_uri()],
                       check=True, capture_output=True, text=True)


def heading_pages(pdf, count):
    from pypdf import PdfReader
    pages = [None] * count
    for number, page in enumerate(PdfReader(pdf).pages, start=1):
        text = re.sub(r"\s+", "", page.extract_text() or "")
        for found in re.findall(rf"{MARK}(\d+){MARK}", text):
            pages[int(found)] = pages[int(found)] or number
    return pages


def build_html_pdf(files, browser):
    output = ROOT / f"{JOB}.pdf"
    try:
        import pypdf  # noqa: F401
    except ImportError:
        print_pdf(build_html(files, ["" for _ in files]), browser, output)
        return False
    print_pdf(build_html(files), browser, output)
    pages = heading_pages(output, len(files))
    print_pdf(build_html(files, [p or "" for p in pages]), browser, output)
    return True


def find_browser():
    for name in BROWSERS:
        found = shutil.which(name) or (Path(name).is_file() and name)
        if found:
            return found
    return None


def main():
    files = code_files()
    build_tex(files)
    pdflatex = shutil.which("pdflatex")
    if not pdflatex:
        browser = find_browser()
        if not browser:
            raise SystemExit(f"No se encontró pdflatex ni Chrome/Chromium/Edge para generar {JOB}.pdf")
        numbered = build_html_pdf(files, browser)
        print(f"Generados {JOB}.tex y {JOB}.pdf en A4 horizontal a dos columnas con {len(files)} códigos.")
        print("Aviso: el PDF se hizo con el navegador porque pdflatex no está instalado.")
        if not numbered:
            print("Aviso: instala pypdf (pip install pypdf) para numerar las hojas en el índice.")
        return
    command = [pdflatex, "-interaction=nonstopmode", "-halt-on-error", f"{JOB}.tex"]
    for _ in range(2):
        result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True,
                                encoding="utf-8", errors="replace")
        if result.returncode:
            raise SystemExit(result.stdout[-4000:] + result.stderr[-1000:])
    print(f"Generados {JOB}.tex y {JOB}.pdf con pdflatex en A4 horizontal a dos columnas ({len(files)} códigos).")


if __name__ == "__main__":
    main()
