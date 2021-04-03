# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# Path setup
# import os, sys
# sys.path.insert(0, os.path.abspath("."))

# Project information
project = "Thorn"
copyright = "2021, Kirill GPRB"
author = "Kirill GPRB"
version = "0.0.1"

# General configuration
extensions = [
    "sphinx.ext.githubpages",
    "sphinx_rtd_theme",
    "myst_parser",
    "breathe",
    "exhale"
]
templates_path = [ "_templates" ]
exclude_patterns = [ "_build", "Thumbs.db", ".DS_Store" ]

# Options for Breathe
breathe_projects = { "thorn": "./xml" }
breathe_default_project = "thorn"

# Options for Exhale
exhale_args = {
    "containmentFolder": "./api",
    "rootFileName": "api_reference.rst",
    "rootFileTitle": "API reference",
    "doxygenStripFromPath": "..",
    "createTreeView": True
}

# Options for domain
primary_domain = "cpp"
highlight_language = "cpp"

# Options for HTML output
html_show_sourcelink = False
html_sidebars = {
    "**": [
        "globaltoc.html",
        "relations.html",
        "sourcelink.html",
        "searchbox.html"
    ]
}
html_static_path = [ "static" ]

import sphinx_rtd_theme
html_theme = "sphinx_rtd_theme"
html_theme_path = [ sphinx_rtd_theme.get_html_theme_path() ]
