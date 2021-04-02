# doxygen
import subprocess, os

def gen_xml(app):
    if os.environ.get("READTHETOCS", None) == True:
        subprocess.call("cd ..; doxygen doc/Doxyfile", shell=True)

def setup(app):
    app.connect("builder-inited", gen_xml)

# project config
project = "Thorn"
version = "0.0.1"
copyright = "2021, Kirill GPRB"
author = "Kirill GPRB"
primary_domain = "cpp"
highlight_language = "cpp"

# extensions
extensions = [ "breathe", "exhale", "sphinx_rtd_theme", "m2r2" ]

# ignore patterns
exclude_patterns = [
    "_build",
    "Thumbs.db",
    ".DS_Store"
]

# breathe config
breathe_projects = { "thorn": "xml" }
breathe_default_project = "thorn"

# exhale config
exhale_args = {
    "containmentFolder": "api",
    "rootFileName": "library_root.rst",
    "rootFileTitle": "API Reference",
    "doxygenStripFromPath": "..",
    "createTreeView": True
}

# html config
html_theme = "sphinx_rtd_theme"
html_static_path = [ "static" ]
