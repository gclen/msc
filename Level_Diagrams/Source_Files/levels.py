import gtk
import numpy as np
import os
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
       
        test_num=0

        #Button to select G09 log file
        a = pack(vbox, gtk.Label())
        a = pack(vbox, gtk.Button(_('Choose Gaussian output file')))
        a.connect('clicked', self.choose_log_file)

        #Button to select fchk file
        a = pack(vbox, gtk.Label())
        a = pack(vbox, gtk.Button(_('Choose fchk file')))
        a.connect('clicked', self.choose_fchk_file) 

        #Dial to set number of occupied orbitals
        self.occ_scale = gtk.Adjustment(value=2, lower=0, upper=100, step_incr=1)
        self.occ_spinner = gtk.SpinButton(self.occ_scale, climb_rate=0, digits= 0)
        self.occ_spinner.set_update_policy(gtk.UPDATE_IF_VALID)
        self.occ_spinner.set_numeric(True)
        pack(vbox, [gtk.Label(_('Number of occupied states desired')),
                    self.occ_spinner])
        self.occ_scale.connect('value-changed', self.scale_occ_orb) 

        #Dial to set number of virtual orbitals
        self.virt_scale = gtk.Adjustment(value=2, lower=0, upper=100, step_incr=1)
        self.virt_spinner = gtk.SpinButton(self.virt_scale, climb_rate=0, digits= 0)
        self.virt_spinner.set_update_policy(gtk.UPDATE_IF_VALID)
        self.virt_spinner.set_numeric(True)
        pack(vbox, [gtk.Label(_('Number of unoccupied states desired')),
                    self.virt_spinner])
        self.virt_scale.connect('value-changed', self.scale_virt_orb) 
        #Button to select atoms
        a = pack(vbox, gtk.Label())
        a = pack(vbox, gtk.Button(_('Select points')))
        a.connect('clicked', self.confirm_points)

        # A close button
        pack(vbox, gtk.Label(_('\n')))
        close = pack(vbox, gtk.Button(_('Close')))
        close.connect('clicked', lambda widget: self.destroy())

        #Button to select atoms
        a = pack(vbox, gtk.Label())
        a = pack(vbox, gtk.Button(_('Run')))
        a.connect('clicked', self.run)
        

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

    #Button for getting fchk file
    def choose_fchk_file(self, button):
        chooser = gtk.FileChooserDialog(title=None,action=gtk.FILE_CHOOSER_ACTION_OPEN, 
                       buttons=(gtk.STOCK_CANCEL,gtk.RESPONSE_CANCEL,gtk.STOCK_OPEN,gtk.RESPONSE_OK))
        chooser.set_current_folder(os.getcwd())
        
        #Set file filters
        file_filter = gtk.FileFilter()
        file_filter.set_name("Formatted checkpoint files")
        file_filter.add_pattern("*.fchk")
        file_filter.add_pattern("*.fch")
        chooser.add_filter(file_filter)        
        file_filter = gtk.FileFilter()
        file_filter.set_name("All files")
        file_filter.add_pattern("*")
        chooser.add_filter(file_filter)

        response = chooser.run()
        if response == gtk.RESPONSE_OK:
            print chooser.get_filename(), 'selected'
        elif response == gtk.RESPONSE_CANCEL:
            print 'Closed, no files selected'
        chooser.destroy()     

    #Button for getting gaussian output file
    def choose_log_file(self, button):
        chooser = gtk.FileChooserDialog(title=None,action=gtk.FILE_CHOOSER_ACTION_OPEN, 
                       buttons=(gtk.STOCK_CANCEL,gtk.RESPONSE_CANCEL,gtk.STOCK_OPEN,gtk.RESPONSE_OK))
        chooser.set_current_folder(os.getcwd())
        
        #Set file filters
        file_filter = gtk.FileFilter()
        file_filter.set_name("Gaussian output files")
        file_filter.add_pattern("*.log")
        file_filter.add_pattern("*.out")
        chooser.add_filter(file_filter)        
        file_filter = gtk.FileFilter()
        file_filter.set_name("All files")
        file_filter.add_pattern("*")
        chooser.add_filter(file_filter)

        response = chooser.run()
        if response == gtk.RESPONSE_OK:
            print chooser.get_filename(), 'selected'
        elif response == gtk.RESPONSE_CANCEL:
            print 'Closed, no files selected'
        chooser.destroy()     

    #Button to run the code
    def run(self, button):
        occ_num = self.occ_spinner.get_value_as_int()
        virt_num = self.virt_spinner.get_value_as_int()
        print occ_num, virt_num

    #Button to get desired number of occupied orbitals
    def scale_occ_orb(self, adjustment):
        return True

    #Button to get desired number of virtual orbitals
    def scale_virt_orb(self, adjustment):
        return True

