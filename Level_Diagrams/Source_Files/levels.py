import gtk
from ase.gui.widgets import pack
from gettext import gettext as _

class Levels(gtk.Window):

    def __init__(self,gui):
        gtk.Window.__init__(self)
        self.set_title('Level Diagrams')
        self.gui = gui
        vbox = gtk.VBox()
        vbox.set_border_width(5)

        # Add elements and show frame
        self.add(vbox)
        vbox.show()
        self.show()

        # A close button
        pack(vbox, gtk.Label(_('\n')))
        close = pack(vbox, gtk.Button(_('Close')))
        close.connect('clicked', lambda widget: self.destroy())        

    



