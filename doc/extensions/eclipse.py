"""
    eclipse

"""

import gzip
import zipfile
import re
from os import path, mkdir, walk
from typing import Any, Dict

from docutils import nodes
from sphinx import addnodes
from sphinx.application import Sphinx
from sphinx.builders.html import StandaloneHTMLBuilder
from sphinx.environment.adapters.indexentries import IndexEntries
from sphinx.util import logging
#from sphinx.util.nodes import NodeMatcher
from sphinx.util.osutil import make_filename



try:
    import xml.etree.ElementTree as etree
except ImportError:
    import lxml.etree as etree  # type: ignore


if False:
    # For type annotation
    from typing import List  # NOQA


logger = logging.getLogger(__name__)

package_dir = path.abspath(path.dirname(__file__))


class EclipseBuilder(StandaloneHTMLBuilder):
    """
    Builder that also outputs an Eclipse plugin.
    """
    name = 'eclipse'

    # don't copy the reST source
    copysource = False
    supported_image_types = ['image/png', 'image/gif', 'image/jpeg', 'image/svg']

    # don't add links
    add_permalinks = False
    # don't add sidebar etc.
    embedded = True

    def init(self):
        # type: () -> None
        super().init()
        self.out_suffix = '.html'
        self.link_suffix = '.html'

    def handle_finish(self):
        # type: () -> None
        self.build_eclipse(self.outdir, self.config.eclipse_pluginname)
        self.finish_tasks.add_task(self.dump_inventory)

    def build_eclipse(self, outdir, outname):
        # type: (str, str) -> None

        # Basic info
        root = etree.Element('toc',
                             label=self.config.html_title,
                             #name=self.config.project,
                             topic="index.html",
                             #version=self.config.version
                             )

        tree = etree.ElementTree(root)


        # TOC

        tocdoc = self.env.get_and_resolve_doctree(
            self.config.master_doc, self, prune_toctrees=False)

        def write_toc(node, parent):
            # type: (nodes.Node, etree.Element) -> None
            if isinstance(node, addnodes.compact_paragraph) or \
               isinstance(node, nodes.bullet_list):
                for subnode in node:
                    write_toc(subnode, parent)
            elif isinstance(node, nodes.list_item):
                item = etree.SubElement(parent, 'topic')
                for subnode in node:
                    write_toc(subnode, item)
            elif isinstance(node, nodes.reference):
                parent.attrib['href'] = node['refuri']
                parent.attrib['label'] = node.astext()


        def istoctree(node):
            # type: (nodes.Node) -> bool
            return isinstance(node, addnodes.compact_paragraph) and \
                'toctree' in node

        for node in tocdoc.traverse(istoctree):
            write_toc(node, root)


        # Dump the XML file
        xmlfile = path.join(outdir, 'toc.xml')
        xmlout = etree.tostring(root, encoding="unicode")

        f = open(xmlfile, 'w')
        f.write('<?xml version=\'1.0\' encoding=\'utf-8\'?>\n' +
                '<?NLS TYPE="org.eclipse.help.toc"?>\n')
        f.write(xmlout.encode("ascii", "xmlcharrefreplace").decode("utf-8"))
        f.close()

        # Write plugin.xml
        pluginxml = path.join(outdir, 'plugin.xml')

        f = open(pluginxml, 'w')
        f.write('<?xml version="1.0" encoding="utf-8"?>\n' +
                '<plugin>\n' +
                '  <extension point="org.eclipse.help.toc">\n' +
                '     <toc file="toc.xml" primary="true"/>\n' +
                '  </extension>\n' +
                '</plugin>')
        f.close()

        # Write manifest
        manifestpath = path.join(outdir, 'META-INF/')
        manifest = path.join(manifestpath, 'MANIFEST.MF')

        if not path.exists(manifestpath):
            mkdir(manifestpath)

        f = open(manifest, 'w')
        f.write('Manifest-Version: 1.0\n' +
                'Ant-Version: Apache Ant 1.10.1\n' +
                'Created-By: 1.8.0_121-b13 (Oracle Corporation)\n' +
                'Bundle-Version: 1.0.0\n' +
                'Bundle-ManifestVersion: 2\n' +
                'Bundle-Localization: plugin\n' +
                'Bundle-Name: ' + self.config.project + '\n' +
                'Bundle-Vendor: Nordic Semiconductor ASA\n' +
                'Eclipse-LazyStart: true\n' +
                'Bundle-SymbolicName: ' + self.config.eclipse_pluginname +
                '; singleton:=true')
        f.close()

        # Create jar file
        jarfile = zipfile.ZipFile(path.join(outdir,
                                            self.config.eclipse_pluginname + '.jar'),
                                  'w', zipfile.ZIP_DEFLATED)
        for rootpath, dirs, files in walk(outdir):
            for file in files:
                if not file.endswith(".jar"):
                    fullfilepath = path.join(rootpath, file)
                    filepath = str.replace(fullfilepath,outdir,"")
                    print("Writing file" + filepath)
                    jarfile.write(fullfilepath,filepath)
        jarfile.close()

def setup(app: Sphinx) -> Dict[str, Any]:
    app.setup_extension('sphinx.builders.html')
    app.add_builder(EclipseBuilder)

    app.add_config_value('eclipse_pluginname', lambda self: make_filename(self.project), None)

    return {
        'version': "0.1",
        'parallel_read_safe': True,
        'parallel_write_safe': True,
    }
