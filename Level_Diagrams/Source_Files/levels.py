import gtk
import numpy as np
from ase.gui.widgets import pack
from gettext import gettext as _
from ase.data import chemical_symbols as symbols
from ase.data import atomic_names as names

class Levels(gtk.Window):

    def __init__(self,gui):
        #Set up window
        gtk.Window.__init__(self)
        self.set_title('Level Diagrams')
        self.gui = gui
        vbox = gtk.VBox()
        vbox.set_border_width(5)

        # A close button
        pack(vbox, gtk.Label(_('\n')))
        close = pack(vbox, gtk.Button(_('Close')))
        close.connect('clicked', lambda widget: self.destroy())

        #Button to select atoms
        a = pack(vbox, gtk.Label())
        a = pack(vbox, gtk.Button(_('Select points')))
        a.connect('clicked', self.confirm_points)

        # Add elements and show frame
        self.add(vbox)
        vbox.show()
        self.show()


    def confirm_points(self, button):
        indices = np.arange(self.gui.images.natoms)[self.gui.images.selected]
        ordered_indices = self.gui.images.selected_ordered
        n = len(indices)
        self.nselected = n

        if n == 2: 
            coords = self.gui.images.P[0][indices]
            print coords
        else:
            points_error = gtk.MessageDialog(type=gtk.MESSAGE_ERROR, buttons=gtk.BUTTONS_NONE) 
            points_error.set_markup("Please select two points")
            points_error.run()

