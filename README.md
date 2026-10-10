# ICPC Team Notebook

Notebook del team **UPC - Turistas**. Los algoritmos viven en archivos `.cpp` y se insertan directamente en [notebook.tex](notebook.tex); al editar el contenido de un código no hay que duplicar el cambio en LaTeX.

## Generación

Ejecuta:

```bash
python3 build_notebook.py
```

Esto actualiza `notebook.tex` y genera `notebook.pdf` con portada, integrantes, índice y una columna en A4 vertical. El generador usa `pdflatex`; si aún no está instalado, usa LibreOffice como alternativa temporal.

En Arch Linux, instala los paquetes necesarios con:

```bash
sudo pacman -S texlive-basic texlive-latex texlive-latexrecommended texlive-latexextra texlive-langspanish
```

## Plantilla de código

Cada algoritmo está preparado para pegarse debajo de las declaraciones de [otros/plantilla.cpp](otros/plantilla.cpp). Para validar individualmente todos los códigos:

```bash
python3 - <<'PY'
from pathlib import Path
import re, subprocess, tempfile

template = Path('otros/plantilla.cpp').read_text()
template = re.sub(r'void solve\(\)\s*\{.*?\n\}', '', template, flags=re.S)
template = re.sub(r'int main\s*\(\)\s*\{.*?\n\}', '', template, flags=re.S)
for source in sorted(Path('.').glob('**/*.cpp')):
    if source.as_posix() in {'otros/plantilla.cpp', 'template.cpp'}:
        continue
    unit = template + '\n' + source.read_text() + '\nint main(){return 0;}\n'
    with tempfile.NamedTemporaryFile(mode='w', suffix='.cpp') as f:
        f.write(unit)
        f.flush()
        subprocess.run(['g++', '-std=c++17', '-fsyntax-only', f.name], check=True)
print('Todos los códigos compilan con la plantilla.')
PY
```

| Plataforma | Usuario | Activo desde |
| ---------- | ------- | ------------ |
| Codeforces | [spigi](https://codeforces.com/profile/spigi) | 2022 |
| Codeforces | [Jean_Pool](https://codeforces.com/profile/iAmJP) | 2024 |
| Codeforces | [Santi2007939](https://codeforces.com/profile/Santi2007939) | 2024 |
| Codeforces | [Chatito17](https://codeforces.com/profile/Chatito17) | 2026 |
