import gtk
import numpy as np
import os
from ase.gui.widgets import pack
from gettext import gettext as _
from ase.data import chemical_symbols as symbols
from ase.data import atomic_names as names

class Levels(gtk.Window):

    def __init__(self,gui):
        #Set defaults
        self.log_file = None
        self.fchk_file = None
        self.coords = None
        self.scaling_method = 'global'
        
        #Set up window
        gtk.Window.__init__(self)
        self.set_title('Level Diagrams')
        self.gui = gui
        vbox = gtk.VBox()
        vbox.set_border_width(5)
        #self.table = gtk.Table(rows=10, columns=2, homogeneous=False)
        #pack(vbox, self.table) 

        #Button to select G09 log file
        a = pack(vbox, gtk.Label())
        self.log_entry_box, b = pack(vbox, [gtk.Entry(max=25), gtk.Button(_('Choose Gaussian output file'))])
        self.log_entry_box.set_max_length(0)
        self.log_entry_box.connect('activate',self.log_entry)
        b.connect('clicked', self.choose_log_file)
        #self.table.attach(self.log_entry_box, 0, 0)
        #self.table.attach(b, 0, 1)

        #Button to select fchk file
        a = pack(vbox, gtk.Label())
        self.fchk_entry_box, b = pack(vbox, [gtk.Entry(max=25), gtk.Button(_('Choose fchk file'))])
        self.fchk_entry_box.set_max_length(0)
        self.fchk_entry_box.connect('activate',self.log_entry)
        b.connect('clicked', self.choose_fchk_file)

        #Dial to set number of occupied orbitals
        self.occ_scale = gtk.Adjustment(value=2, lower=0, upper=100, step_incr=1)
        self.occ_spinner = gtk.SpinButton(self.occ_scale, climb_rate=0, digits= 0)
        self.occ_spinner.set_update_policy(gtk.UPDATE_IF_VALID)
        self.occ_spinner.set_numeric(True)
        pack(vbox, [gtk.Label(_('Number of occupied states ')),
                    self.occ_spinner])
        self.occ_scale.connect('value-changed', self.scale_occ_orb) 

        #Dial to set number of virtual orbitals
        self.virt_scale = gtk.Adjustment(value=2, lower=0, upper=100, step_incr=1)
        self.virt_spinner = gtk.SpinButton(self.virt_scale, climb_rate=0, digits= 0)
        self.virt_spinner.set_update_policy(gtk.UPDATE_IF_VALID)
        self.virt_spinner.set_numeric(True)
        pack(vbox, [gtk.Label(_('Number of unoccupied states ')),
                    self.virt_spinner])
        self.virt_scale.connect('value-changed', self.scale_virt_orb) 

        #Dial to set number of bins
        self.bin_scale = gtk.Adjustment(value=100, lower=0, upper=500, step_incr=1)
        self.bin_spinner = gtk.SpinButton(self.bin_scale, climb_rate=5, digits= 0)
        self.bin_spinner.set_update_policy(gtk.UPDATE_IF_VALID)
        self.bin_spinner.set_numeric(True)
        pack(vbox, [gtk.Label(_('Number of bins ')),
                    self.bin_spinner])
        self.bin_scale.connect('value-changed', self.scale_bin_num) 

        #Button to select atoms
        a = pack(vbox, gtk.Label())
        a, b = pack(vbox, [gtk.Label(_('Select two points and click Confirm')), 
                           gtk.Button(_('Confirm'))])
        b.connect('clicked', self.confirm_points)

        #Button to set scaling
        a = pack(vbox, gtk.Label('Scaling method'))
        button = pack(vbox, gtk.RadioButton(None, "Global"))
        button.connect("toggled", self.set_scaling_method, "global")
        button.show()
        
        button = pack(vbox, gtk.RadioButton(button, "Orbital"))
        button.connect("toggled", self.set_scaling_method, "orbital")
        button.show()

        #Button to set all of the parameters
        a = pack(vbox, gtk.Label())
        a = pack(vbox, gtk.Button(_('Run')))
        a.connect('clicked', self.run_SOLD)
        

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
            self.coords = self.gui.images.P[0][indices]
        else:
            points_error = gtk.MessageDialog(type=gtk.MESSAGE_ERROR, buttons=gtk.BUTTONS_NONE) 
            points_error.set_markup("Please select two points")
            points_error.run()

    def log_entry(self, widget):
        self.log_file = widget.get_text()   

    def fchk_entry(self, widget):
        self.fchk_file = widget.get_text()             

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
            self.fchk_file = chooser.get_filename()
            self.fchk_entry_box.set_text(self.fchk_file)
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
            self.log_file = chooser.get_filename()
            self.log_entry_box.set_text(self.log_file)
        elif response == gtk.RESPONSE_CANCEL:
            print 'Closed, no files selected'
        chooser.destroy()     


    #Button to get desired number of occupied orbitals
    def scale_occ_orb(self, adjustment):
        return True

    #Button to get desired number of virtual orbitals
    def scale_virt_orb(self, adjustment):
        return True

    def scale_bin_num(self, adjustment):
        return True
    
    def set_scaling_method(self, widget ,data='global'):
        if data == 'orbital' and widget.get_active()==True:
            self.scaling_method = 'orbital'
        elif data == 'global' and widget.get_active() == True:
            self.scaling_method = 'global'

    #Button to run the code
    def run_SOLD(self, button):
        #Check that all parameters have been set
        if self.log_file == None:
            log_error = gtk.MessageDialog(type=gtk.MESSAGE_ERROR, buttons=gtk.BUTTONS_NONE) 
            log_error.set_markup("Please select a Gaussian output file and run again")
            log_error.run()
        if self.fchk_file == None:
            fchk_error = gtk.MessageDialog(type=gtk.MESSAGE_ERROR, buttons=gtk.BUTTONS_NONE) 
            fchk_error.set_markup("Please select a formatted checkpoint file and run again")
            fchk_error.run()
        if self.coords == None:
            points_error = gtk.MessageDialog(type=gtk.MESSAGE_ERROR, buttons=gtk.BUTTONS_NONE) 
            points_error.set_markup("Please select two atoms to use as points")
            points_error.run()            
        
        #Write config and run code
        else:
            self.write_config()
            os.system('SOLD < levels_config.txt')     
            os.system('SOLD_plot.py')


    def write_config(self):     
        occ_num = str(self.occ_spinner.get_value_as_int())
        virt_num = str(self.virt_spinner.get_value_as_int())
        bin_num = str(self.bin_spinner.get_value_as_int())
    
        #Write out the parameters to a config file
        config_file = open('levels_config.txt', 'w')
            
        config_file.write(self.log_file + '\n')
        config_file.write(self.fchk_file + '\n')
        config_file.write(occ_num + '\n')
        config_file.write(virt_num + '\n')
        
        for i in range(len(self.coords)):
            coord_string = str(self.coords[i][0]) + ' ' + str(self.coords[i][1]) + ' ' + str(self.coords[i][2]) 
            config_file.write(coord_string + '\n')

        config_file.write(bin_num + '\n')
        config_file.write(self.scaling_method + '\n')


