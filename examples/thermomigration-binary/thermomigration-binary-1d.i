################## The numerical parameters in this code are assigned for a general binary A-B system 
################## In order to develop model for Cu-Sn materials system, the parameters of Ref. has to be used.
[Mesh]
    type = GeneratedMesh
    dim = 1
    nx = 1400 #250 #150 nx>=20 for meeting criteria of Kunwar2017-ICEPT (Eqs. 1 and 2) 
    ny = 0 #2000 #250 #150
    nz = 0
    xmin = 0
    xmax = 2000 #0.82 #8.20 um (length scale 1 hm= 0.1 um) 40 3.0 um (FCC) + 0.2 um (IMC) + 5.0 um (Liquid) length_scale=0.1 nm
    ymin = 0  # If given greater than ymax, Error prompt = "Periodic boundary neighbour not found"
    ymax = 0 #100 #0.82 #8.20 um (length scale 1 hm = 0.1 um) 40 There is no unit such as hm, i use it as a short form of 10^-7 m
    zmin = 0
    zmax = 0
    #elem_type = QUAD4
[]

[BCs]
   #[./Periodic]
       # [./y]
          ##  auto_direction = 'x y'
           # auto_direction = 'y '
           # variable = 'c w c_cu c_imc c_sn eta_cu eta_imc eta_sn'
        #[../]
    #[../]
    #Eta variable boundary conditions
    [./neumann1] #middle of liquid in physical domain
        type = NeumannBC
        boundary = 'right'
        variable = 'eta_cu'
        value = 0
    [../]
    [./neumann2] #anode
       type = NeumannBC
        boundary = 'left'
        variable = 'eta_sn'
        value = 0
   [../]
   #Temperature variable boundary conditions
   #[./dirichlet_T1] #middle of liquid in physical domain (relatively hotter side)
      # type = DirichletBC
      # boundary = 'right'
      # variable = 'temp'
      # value = 523.150
    #[../]
    #[./neumann_Ta] #anode Cu
      # type = NeumannBC
      #  boundary = 'left'
      #  variable = 'temp'
      #  value = -1.70E-11 #j=5.0E+2 A/cm2=5.0E+6 A/m2 = 5.0E-12 A/nm2 grad_u = -j*rho_cu V/m i.e. factor= 1.0/(length_scale)
   #[../]
   #[./neumann_Tmid] #anode Sn
      # type = NeumannBC
      #  boundary = 'right'
      #  variable = 'temp'
      #  value = -1.10E-10 #5.0E+2 A/cm2=5.0E+6 A/m2 = 5.0E-12 A/nm2 i.e. factor= 1.0/(length_scale^2)
   #[../]
    #[./dirichlet_T2] #left edge of cold copper sink
      # type = DirichletBC
      # boundary = 'left'
      # variable = 'temp'
      #  value = 523.129525 # delta_T = 0.01365 K/um = 1.365E-02 K/um Zhao2015-srep
    #[../]
[]


[Variables]
    # concentration Sn
    [./c]
        order = FIRST
        family = LAGRANGE
        scaling=1.0E-08 
    [../]
    # chemical potential
    [./w]
       order = FIRST
       family = LAGRANGE
       scaling=1.0E-13
    [../]

    # phase concentration  Sn in Cu (Sn2.0Cu)
    [./c_cu]
        order = FIRST
        family = LAGRANGE
        initial_condition = 0.026 #Artificial 0.3266 # # Guan2015-JAC
        scaling=1.0E-09 #8   
    [../]

    # phase concentration  Sn in Cu6Sn5
    [./c_imc]
        order = FIRST
        family = LAGRANGE
        initial_condition = 0.455 # Guan2015-JAC instead of 0.4155
        scaling=1.0E-08 
    [../]

    # phase concentration  Sn in Sn
    [./c_sn]
        order = FIRST
        family = LAGRANGE
        initial_condition = 0.95 #98.00 % Sn
        scaling=1.0E-05  
    [../]

    # order parameter Cu
    [./eta_cu]
       order = FIRST
       family = LAGRANGE
       scaling=1.0E-02
    [../]
    # order parameter Cu6Sn5
    [./eta_imc]
        order = FIRST
        family = LAGRANGE
        scaling=1.0E-02
    [../]

    # order parameter Sn
    [./eta_sn]
        order = FIRST
        family = LAGRANGE
     #initial_condition = 0.0
       scaling=1.0E+00 #3
    [../]
    # temperature
    #[./temp] 
       # initial_condition = 523.1397625 # V unit 1 mV Average of two extreme temperatures
       # order = FIRST
       # family = LAGRANGE
       # scaling=1.0E-08 
    #[../]
[]


[ICs]
    [./eta1] #Cu 81 um* 30 um
        variable = eta_cu
        type = FunctionIC
        function = 'if(x>=0&x<=700,1,0)'
        #function = 'r:=sqrt((x-20)^2+(y-20)^2);if(r<=8,1,0)'
    [../]
    [./eta2] #Cu6Sn5
        variable = eta_imc
        type = FunctionIC
        function = 'if(x>700&x<=800,1,0)'
        #function = 'r:=sqrt((x-20)^2+(y-20)^2);if(r>8&r<=16,1,0)'
    [../]
    [./eta3] #Sn
        variable = eta_sn
        type = FunctionIC
        function = 'if(x>800&x<=2000,1,0)'
        #function = 'r:=sqrt((x-20)^2+(y-20)^2);if(r>16,1,0)'
    [../]

    [./c] #Concentration of Sn
        variable = c
        #args = 'eta_cu eta_imc eta_sn'
        type = FunctionIC
        function = '0.02574*if(x<=700,1,0)+0.455*if(x>700&y<=800,1,0)+0.9633*if(x>800,1,0)' #TODO: Make nicer, should be possible to use values of the other variables.
        #function = '0.3266*if(y<=50,1,0)+0.4255*if(y>50&y<=100,1,0)+0.9633*if(y>100,1,0)' #TODO: Make nicer, should be possible to use values of the other variables. Artificial
        #function = '0.2*if(sqrt((x-40)^2+(y-40)^2)<=10,1,0)+0.5*if(sqrt((x-40)^2+(y-40)^2)>10&sqrt((x-40)^2+(y-40)^2)<=18,1,0)+0.8*if(sqrt((x-40)^2+(y-40)^2)>18,1,0)' #TODO: Make nicer, should be possible to use values of the other variables.
        #function = '0.01*if(sqrt((x-20)^2+(y-20)^2)<=8,1,0)+0.417*if(sqrt((x-20)^2+(y-20)^2)>8&sqrt((x-20)^2+(y-20)^2)<=16,1,0)+0.99*if(sqrt((x-20)^2+(y-20)^2)>16,1,0)' #TODO: Make nicer, should be possible to use values of the other variables.
    [../]
[]

[Materials]
  #scalings
  [./scale]
    type = GenericConstantMaterial
    prop_names = 'length_scale energy_scale time_scale'
    prop_values = '1e09 6.24150943e18 1.0e09' #m to hm(imaginary) J to eV s to h ev*10^27
    #prop_values = '1e10 1.0E45 1.0E-6' #m to hm(imaginary) J to uJ s to h
  [../]
  # With using the scaling constants all other units can be used in SI units
  [./model_constants]
    type = GenericConstantMaterial
    prop_names = 'sigma delta delta_real gamma R T tgrad_corr_mult'
    #prop_values = '0.5 4.0e-7 5e-10 1.5 8.3145 523.15 0' #J/m^2 m J/mol/K K - ?
    prop_values = '0.5 23.330e-09 5e-11 1.5 8.3145 523.15 0' #J/m^2 m J/mol/K K - ? # For varying mu and kappa delta=2*dx
    #prop_values = '0.5 1.00e-07 5e-09 1.5 8.3145 523.15 0' #J/m^2 m J/mol/K K - ? # For varying mu and kappa delta=2*dx
  [../]
    #Free energy (Please delete the 100 factor used for correct representation)
    # chemical free energy is represented as fbk instead of its common form fch since fch has been used to represent fbk+fem 
    # and fch is used extensively in the CH kernels and AC kernels in the original code
    #Free energy (eV/hm^3) let 1 hm = 0.1 um
    # 1 J = 6.242E+18 eV
    # 1 m^3/mol = 10^21 hm^3/mol (Vm)
     # Case A - Aeta Bcu Ceta 
    [./fbk_cu] #Chemical energy Cu phase
        type = DerivativeParsedMaterial
        f_name = fbk_cu
        args = 'c_cu'
        material_property_names = 'energy_scale length_scale'
        constant_names = 'factor1 Vmcu Acu Bcu Ccu  '
        constant_expressions = '1.0  16.29E-06 4.6428E+04 8.257E+01 -2.96E+04 ' #7.124E-6 Molar Volume, Li2013
        function = 'factor1*(energy_scale/length_scale^3)*(0.5*Acu*(c_cu-0.6353)^2+Bcu*(c_cu-0.6353)+Ccu)/Vmcu' # Free energy density from Calphad calculation
        #function = 'factor1*(energy_scale/length_scale^3)*(0.5*Acu*(c_cu-0.02574)^2+Bcu*(c_cu-0.02574)+Ccu)/Vmcu' # Free energy density from Calphad calculation
        # function = '30.*(c_cu-0.10569)^2+1.*(c_cu-0.10569)+0.5' # Toy free energy for working tutorial
        outputs = exodus
    [../]
    # The free energy is multiplied by 100 to see if it affects the result
    [./fbk_imc] #Chemical energy IMC phase
        type = DerivativeParsedMaterial
        f_name = fbk_imc
        args = 'c_imc'
        material_property_names = 'energy_scale length_scale'
        constant_names = 'factor2 Vmimc Aimc Bimc Cimc'
        constant_expressions = '1.01882 16.29E-06 1.966E+06 8.257E+01 -2.96E+04 ' #10.6E-06 - Molar Volume, Li2013
        #function = '(energy_scale/length_scale^3)*(0.5*Aimc*(c_imc-0.444)^2+Bimc*(c_imc-0.444)+Cimc)/Vmimc' # Free energy density from Calphad calculation
        #function = 'factor2*(energy_scale/length_scale^3)*(0.5*Aimc*(c_imc-0.4349)^2+Bimc*(c_imc-0.4349)+Cimc)/Vmimc' # Free energy density from Calphad calculation
        function = 'factor2*(energy_scale/length_scale^3)*(0.5*Aimc*(c_imc-0.4349)^2+Bimc*(c_imc-0.4349)+Cimc)/Vmimc' # Free energy density from Calphad calculation
        #  function = '60.*(c_imc-0.41753)^2'
        outputs = exodus
    [../]
    [./fbk_sn] #Chemical energy Sn phase
        type = DerivativeParsedMaterial
        f_name = fbk_sn
        args = 'c_sn'
        material_property_names = 'energy_scale length_scale'
        constant_names = 'factor3 Vmsn Asn Bsn Csn'
        constant_expressions = '1.0 16.29E-06 4.6552E+04 2.054E+03 -2.8749E+04 '
        #function = 'factor3*(energy_scale/length_scale^3)*(0.5*Asn*(c_sn-0.8617)^2+Bsn*(c_sn-0.8617)+Csn)/Vmsn' # Free energy density from Calphad calculation
        function = 'factor3*(energy_scale/length_scale^3)*(0.5*Asn*(c_sn-0.9467)^2+Bsn*(c_sn-0.9467)+Csn)/Vmsn' # Free energy density from Calphad calculation
        # function = '30.*(c_sn-0.99941)^2+2.*(c_sn-0.99941)+1.'
        outputs = exodus
    [../]

   # Electromigration free energy density
   # [./ftm_cu] #EM energy Sn phase
     #   type = DerivativeParsedMaterial
     #   f_name = ftm_cu
     #   args = 'c_cu temp' 
     #   material_property_names = 'energy_scale length_scale'
     #   constant_names = 'factore1 Vmcu  Qheatcucu Qheatcusn' #Qheat is heat of transport in J/mol
     #   constant_expressions = '-1.0 16.29E-06 1.112E+04 1.112E+04 '
     #   #function = 'factor3*(energy_scale/length_scale^3)*(0.5*Asn*(c_sn-0.8617)^2+Bsn*(c_sn-0.8617)+Csn)/Vmsn' # Free energy density from Calphad calculation
     #   #function = 'factore1*(energy_scale/length_scale^3)*(Nav*echarge*pot*zeffcu*c_cu)/Vmcu' # Free energy density from Calphad calculation
     #   function = 'factore1*(energy_scale/length_scale^3)*(log(temp/523.15)*(Qheatcusn*c_cu+Qheatcucu*(1.0-c_cu)))/Vmcu' 
      #  # function = '30.*(c_sn-0.99941)^2+2.*(c_sn-0.99941)+1.'
      #  outputs = exodus
    #[../]
   #[./ftm_imc] #EM energy Sn phase
     #   type = DerivativeParsedMaterial
     #   f_name = ftm_imc
     #   args = 'c_imc temp' 
     #   material_property_names = 'energy_scale length_scale'
      #  constant_names = 'factore2 Vmimc Qheatimccu Qheatimcsn '
      #  constant_expressions = '-1.0 16.29E-06 2.224E+04 2.224E+04 '
      #  #function = 'factor3*(energy_scale/length_scale^3)*(0.5*Asn*(c_sn-0.8617)^2+Bsn*(c_sn-0.8617)+Csn)/Vmsn' # Free energy density from Calphad calculation
      #  function = 'factore2*(energy_scale/length_scale^3)*(log(temp/523.15)*(Qheatimcsn*c_imc+Qheatimccu*(1.0-c_imc)))/Vmimc' # Free energy density from Calphad calculation
      #  # function = '30.*(c_sn-0.99941)^2+2.*(c_sn-0.99941)+1.'
      #  outputs = exodus
    #[../]
   #[./ftm_sn] #EM energy Sn phase
       # type = DerivativeParsedMaterial
       # f_name = ftm_sn
      #  args = 'c_sn temp' 
       # material_property_names = 'energy_scale length_scale'
       # constant_names = 'factore3 Vmsn Qheatsncu Qheatsnsn'
       # constant_expressions = '-1.0 16.29E-06 1.112E+04 1.112E+04 '
      #  #function = 'factor3*(energy_scale/length_scale^3)*(0.5*Asn*(c_sn-0.8617)^2+Bsn*(c_sn-0.8617)+Csn)/Vmsn' # Free energy density from Calphad calculation
       # function = 'factore3*(energy_scale/length_scale^3)*(log(temp/523.15)*(Qheatsnsn*c_sn+Qheatsncu*(1.0-c_sn)))/Vmsn' # Free energy density from Calphad calculation
       # # function = '30.*(c_sn-0.99941)^2+2.*(c_sn-0.99941)+1.'
       # outputs = exodus
    #[../]
    # Derivative sum material mateial to add fbk_i + fem_i = fch_i

  #sum chemical and electromigration energies
  [./fch_cu]
    type = DerivativeSumMaterial
    f_name = fch_cu
    args = 'c_cu '
    sum_materials = 'fbk_cu'
    #sum_materials = 'fch0'
    #use_displaced_mesh = true
    outputs = exodus
  [../]
  [./fch_imc]
    type = DerivativeSumMaterial
    f_name = fch_imc
    args = 'c_imc eta_cu eta_imc eta_sn'
    sum_materials = 'fbk_imc '
    #sum_materials = 'fch2'
    #use_displaced_mesh = true
    outputs = exodus
  [../]
  [./fch_sn]
    type = DerivativeSumMaterial
    f_name = fch_sn
    args = 'c_sn '
    sum_materials = 'fbk_sn '
    #sum_materials = 'fch3'
    #use_displaced_mesh = true
    outputs = exodus
  [../]

    #SwitchingFunction
    [./h_cu]
        type = SwitchingFunctionMultiPhaseMaterial
        h_name = h_cu
        all_etas = 'eta_cu eta_imc eta_sn'
        phase_etas = eta_cu
        outputs = exodus
    [../]

    [./h_imc]
        type = SwitchingFunctionMultiPhaseMaterial
        h_name = h_imc
        all_etas = 'eta_cu eta_imc eta_sn'
        phase_etas = eta_imc
        outputs = exodus
    [../]

    [./h_sn]
        type = SwitchingFunctionMultiPhaseMaterial
        h_name = h_sn
        all_etas = 'eta_cu eta_imc eta_sn'
        phase_etas = eta_sn
        outputs = exodus
    [../]

    #Double well, not used
    [./g_cu]
      type = BarrierFunctionMaterial
      g_order = SIMPLE
      eta=eta_cu
      well_only = True
      function_name = g_cu
    [../]
    #Double well, not used
    [./g_imc]
      type = BarrierFunctionMaterial
      g_order = SIMPLE
      eta=eta_imc
      well_only = True
      function_name = g_imc
    [../]
    #Double well, not used
    [./g_sn]
      type = BarrierFunctionMaterial
      g_order = SIMPLE
      eta=eta_sn
      well_only = True
      function_name = g_sn
    [../]

    ## constant properties
    #[./mob]
    #    type = GenericConstantMaterial
    #    prop_names  = 'M L'
    #    prop_values = '3. 3.'
    #[../]
    # For grain boundary diffusion
    #[./Mgb]
      #type=ParsedMaterial
      #material_property_names = 'D_gb delta delta_real h0(eta0,eta1,eta2,eta3) h1(eta0,eta1,eta2,eta3) h2(eta0,eta1,eta2,eta3) h3(eta0,eta1,eta2,eta3) A_cu A_eps A_eta A_sn length_scale energy_scale time_scale'
      #f_name = Mgb
      #function = '(length_scale^2/(energy_scale*time_scale))*3.*D_gb*delta_real/((h0*A_cu+h1*A_eps+h2*A_eta+h3*A_sn)*delta)'
     # #function = '4e-5'
    #[../]
    [./CHMobility]
        type = DerivativeParsedMaterial
        f_name = M  
        args = 'eta_cu eta_imc eta_sn'
        constant_names = 'factor_M M_cu M_imc M_sn' # Use Equation 25 of Hektor2016 paper M=sigma_hiMi, where Mi=D_i/A_i and A_i = coeff of parabolic free energy
        constant_expressions = '1.0 2.154E-24 1.558E-22 4.296E-17' #m^2 mol/J s mobility of Sn is used as 10E-23 to be near to that of Cu and IMC
        material_property_names = 'h_cu(eta_cu,eta_imc,eta_sn) h_imc(eta_cu,eta_imc,eta_sn) h_sn(eta_cu,eta_imc,eta_sn) length_scale energy_scale time_scale'
        function = 'factor_M*(length_scale^5/(energy_scale*time_scale))*(M_cu*h_cu+M_imc*h_imc+M_sn*h_sn)' #+h_imc*Mgb Mgb is kept as 1.5581E-19
        #function = 'factor_M*(length_scale^5/(energy_scale*time_scale))*(M_cu*h_cu+(M_imc+1.5581E-19)*h_imc+M_sn*h_sn)' #+h_imc*Mgb Mgb is kept as 1.5581E-19
    [../]
    [./kappa]
    type = ParsedMaterial
    constant_names = 'factor_kappa ' # https://mooseframework.inl.gov/old/wiki/MooseTutorials/IronChromiumDecomposition/SimpleTestModel/    
    constant_expressions = '1.0 ' # factor for kappa and mu and free energy
    material_property_names = 'sigma delta length_scale energy_scale'
    f_name = kappa
    function = 'factor_kappa*0.75*sigma*delta*energy_scale/length_scale' #eV/hm
    [../]
     [./mu]
    type = ParsedMaterial
    constant_names = 'factor_mu ' # https://mooseframework.inl.gov/old/wiki/MooseTutorials/IronChromiumDecomposition/SimpleTestModel/    
    constant_expressions = '1.0 ' # factor for kappa and mu and free energy
    material_property_names = 'sigma delta length_scale energy_scale'
    f_name = mu
    function = 'factor_mu*6*(sigma/delta)*energy_scale/length_scale^3' #eV/hm^3
    [../]
    #[./ACMobility] #l^3/et unit
        #type = DerivativeParsedMaterial
        #f_name = L
        #args = 'eta_cu eta_imc eta_sn'
        #material_property_names = 'M(eta_cu,eta_imc,eta_sn)' # Use Equation 29 of Hektor2016 article
        ##function = 'M_cu*h_cu+M_imc*h_imc+M_sn*h_sn'
        ##function = '(0.5*eta_cu^2*eta_imc^2*(M_cu+M_imc)+0.5*eta_sn^2*eta_imc^2*(M_sn+M_imc)+0.5*eta_cu^2*eta_sn^2*(M_cu+M_sn))/(eta_cu^2*eta_imc^2+eta_cu^2*eta_sn^2+eta_sn^2*eta_imc^2)'
        #function = '10.*M'
    #[../]
    #https://github.com/jhektor/Puffin/blob/master/inputfiles/220C/lineepseta_broken.i
# Trying to be in accordance with Eq. 29 of Hektor et al, 2016 Acta Mater Vol. 108
# L is a proportional factor of M
  [./L_cu_eta]
    type = ParsedMaterial
    material_property_names = 'mu kappa length_scale energy_scale time_scale'
    constant_names = 'factor4 M_cu M_imc Vmcu Vmimc' # Use Equation 25 of Hektor2016 paper M=sigma_hiMi, where Mi=D_i/A_i and A_i = coeff of parabolic free energy
    constant_expressions = '1.0E+09 2.154E-24 1.558E-22 7.124E-6 16.29E-06 ' #m^2 mol/J s # works for 1.0E+05 also works
    f_name = L_cu_eta
    function = 'factor4*(length_scale^3/(energy_scale*time_scale))*mu*1.0*(M_cu + M_imc)/(3*kappa*(0.2097-0.4299)^2)' #hm^3/eVs
  [../]
  [./L_eta_sn]
    type = ParsedMaterial
    constant_names = 'factor5 M_imc M_sn Vmimc Vmsn' # Use Equation 25 of Hektor2016 paper M=sigma_hiMi, where Mi=D_i/A_i and A_i = coeff of parabolic free energy
    constant_expressions = '1.0E+09 1.558E-22 4.296E-17 10.6E-06 16.29E-06 ' #m^2 mol/J s
    material_property_names = 'mu kappa length_scale energy_scale time_scale'
    f_name = L_eta_sn
    function = 'factor5*(length_scale^3/(energy_scale*time_scale))*mu*1.0*(M_sn + M_imc)/(3*kappa*(0.4356-0.9587)^2)' #hm^3/eVs'
  [../]
  [./L_cu_sn]
    type = ParsedMaterial
    constant_names = 'factor6 M_cu M_sn Vmcu Vmsn' # Use Equation 25 of Hektor2016 paper M=sigma_hiMi, where Mi=D_i/A_i and A_i = coeff of parabolic free energy
    constant_expressions = '1.0E+09 2.154E-24  4.296E-17 7.124E-6 16.29E-06' #m^2 mol/J s
     material_property_names = 'mu kappa  length_scale energy_scale time_scale'
     f_name = L_cu_sn
    function = 'factor6*(length_scale^3/(energy_scale*time_scale))*mu*1.0*(M_cu + M_sn)/(3*kappa*(0.6015-0.9348)^2)' #hm^3/eVs
  [../]
  #[./L_imc_imc]
  #  type = ParsedMaterial
  #  material_property_names = 'L_cu_imc L_imc_sn'
  #  f_name = L_imc_imc
  #  function = 'L_cu_imc'
  #[../]
    [./ACMobility]
        type = DerivativeParsedMaterial
        f_name = L
        args = 'eta_cu eta_imc eta_sn'
        #material_property_names = 'L_cu_eps L_cu_eta L_cu_sn L_eps_eta L_eps_sn L_eta_sn'
        material_property_names = 'L_cu_eta  L_eta_sn L_cu_sn'
        # Added epsilon to prevent division by 0 (Larry Aagesen)
        #function ='pf:=1e5;eps:=0.01;(L_cu_eps*(pf*eta_cu^2+eps)*(pf*eta_imc1^2+eps)+L_cu_eta*(pf*eta_cu^2+eps)*(pf*eta_imc2^2+eps)+L_eps_sn*(pf*eta_imc1^2+eps)*(pf*eta_sn^2+eps)+L_eps_eta*(pf*eta_imc1^2+eps)*(pf*eta_imc2^2+eps)+L_eta_sn*(pf*eta_imc2^2+eps)*(pf*eta_sn^2+eps)+L_cu_sn*(pf*eta_cu^2+eps)*(pf*eta_sn^2+eps))/((pf*eta_cu^2+eps)*((pf*eta_imc1^2+eps)+(pf*eta_imc2^2+eps))+((pf*eta_imc1^2+eps)+(pf*eta_imc2^2+eps))*(pf*eta_sn^2+eps)+(pf*eta_cu^2+eps)*(pf*eta_sn^2+eps)+(pf*eta_imc1^2+eps)*(pf*eta_imc2^2+eps))'
        #**#function ='pf:=1e5;eps:=1e-5;(L_cu_eta*(pf*eta_cu^2+eps)*(pf*eta_imc^2+eps)+L_eta_sn*(pf*eta_imc^2+eps)*(pf*eta_sn^2+eps))/((pf*eta_cu^2+eps)*(pf*eta_imc^2+eps)+(pf*eta_imc^2+eps)*(pf*eta_sn^2+eps))'
        # the numbers must be corrected before L_i_j
        function ='L_eta_sn'

        # Conditional function (Daniel Schwen)
        #function ='numer:=L_cu_eps*eta0^2*eta1^2+L_eps_eta*eta1^2*eta2^2+L_eta_sn*eta2^2*eta3^2;denom:=eta0^2*eta1^2+eta1^2*eta2^2+eta2^2*eta3^2;if(denom!=0,numer/denom,0.)'
        #function ='numer:=L_cu_eps*eta0^2*eta1^2+L_eps_eta*eta1^2*eta2^2+L_eta_sn*eta2^2*eta3^2;denom:=eta0^2*eta1^2+eta1^2*eta2^2+eta2^2*eta3^2;if(denom>0.0001,numer/denom,0.)'

        derivative_order = 2
        #outputs = exodus_out
        outputs = exodus
    [../]
    # constant properties
    #[./constants]
        #type = GenericConstantMaterial
        #prop_names  = 'kappa gamma mu tgrad_corr_mult'
        #prop_values = '0.5 0.5 1. 0.'
    #[../]

   #[./thermcond] # change it into units of thermal conductivity rather than electrical conductivity
       # type = DerivativeParsedMaterial
       # f_name = thermcond # Use this name in D_name of MatDiffusion kernel 
       # args = 'eta_cu eta_imc eta_sn'
       # constant_names = 'factor_ec tc_cu tc_imc tc_sn' # Use Equation 25 of Hektor2016 paper M=sigma_hiMi, where Mi=D_i/A_i and A_i = coeff of parabolic free energy
       # constant_expressions = '1.0 400.0 40.00 35.00' #m^2 mol/J s mobility of Sn is used as 10E-23 to be near to that of Cu and IMC
       # material_property_names = 'h_cu(eta_cu,eta_imc,eta_sn) h_imc(eta_cu,eta_imc,eta_sn) h_sn(eta_cu,eta_imc,eta_sn) length_scale energy_scale time_scale'
       # function = 'factor_ec*(energy_scale/(length_scale*time_scale))*(tc_cu*h_cu+(tc_imc)*h_imc+tc_sn*h_sn)' # Unit of thcond is W/m K = (J/(m s K))
   # [../]
[]

[Kernels]
    #Kernels for split Cahn-Hilliard equation without composition gradent term(?)
    # Cahn-Hilliard Equation
    #
    [./CHBulk] # Gives the residual for the concentration, dF/dc-mu
        type = KKSSplitCHCRes
        variable = c
        ca       = c_imc
        cb       = c_sn
        fa_name  = fch_imc #only fa is used
        fb_name  = fch_sn
        #args_a = 'c_cu'
        w        = w
        h_name   = h_imc
        args = 'eta_cu eta_imc eta_sn ' #added after a warning
    [../]

    [./dcdt] # Gives dc/dt
        type = CoupledTimeDerivative
        variable = w
        v = c
    [../]
    [./ckernel] # Gives residual for chemical potential dc/dt+M\grad(mu)
        type = SplitCHWRes  #Ok if M is not depending on c or w
        mob_name = M
        variable = w
        args = 'eta_cu eta_imc eta_sn'
    [../]

    #KKS conditions
    # enforce pointwise equality of chemical potentials, n-1 kernels needed (mu_1=mu_2, mu_2=mu_3, ..., mu_n-1=mu_n
    [./chempot_cu_imc]
      type = KKSPhaseChemicalPotential
      variable = c_cu
      cb       = c_imc
      fa_name  = fch_cu
      fb_name  = fch_imc
      args = 'eta_cu eta_imc eta_sn ' #added after a warning
    [../]
    [./chempot_sn_cu]
      type = KKSPhaseChemicalPotential
      variable = c_imc
      cb       = c_sn
      fa_name  = fch_imc
      fb_name  = fch_sn
      args = 'eta_cu eta_imc eta_sn ' #added after a warning
    [../]

    [./phaseconcentration] # enforce c = sum h_i*c_i
      type = KKSMultiPhaseConcentration
      variable = c_sn
      cj = 'c_cu c_imc c_sn'
      hj_names = 'h_cu h_imc h_sn'
      etas = 'eta_cu eta_imc eta_sn'
      c = c
    [../]

    #Kernels for Allen-Cahn equation for Cu
    [./detadt_cu]
      type = TimeDerivative
      variable = eta_cu
    [../]
    [./ACBulkF_cu] # sum_j dh_j/deta_i*F_j+w*dg/deta_i, last term is not used(?)
      type = KKSMultiACBulkF
      variable  = eta_cu
      Fj_names  = 'fch_cu fch_imc fch_sn'
      hj_names  = 'h_cu h_imc h_sn'
      gi_name   = g_cu
      eta_i     = eta_cu
      wi        = 1
      mob_name = L
      args      = 'c_cu c_imc c_sn eta_imc eta_sn '
    [../]
    [./ACBulkC_cu] # -L\sum_j dh_j/deta_i*mu_jc_j
      type = KKSMultiACBulkC
      variable  = eta_cu
      Fj_names  = 'fch_cu fch_imc fch_sn'
      hj_names  = 'h_cu h_imc h_sn'
      cj_names  = 'c_cu c_imc c_sn'
      eta_i     = eta_cu
      mob_name = L
      args      = 'eta_imc eta_sn '
    [../]
    [./ACInterface_cu] # L*kappa*grad\eta_i
      type = ACInterface
      variable = eta_cu
      kappa_name = kappa
      mob_name = L
      args      = 'eta_imc eta_sn'
      variable_L = true
    [../]
    [./ACdfintdeta_cu] #L*m*(eta_i^3-eta_i+2*beta*eta_i*sum_j eta_j^2)
      type = ACGrGrMulti #Jacobian not correct for non-constant mobility?
      variable = eta_cu
      v = 'eta_imc eta_sn'
      gamma_names = 'gamma gamma'
      mob_name = L
      args = 'eta_imc eta_sn'
    [../]

    #Kernels for Allen-Cahn equation for Cu6Sn5
    [./detadt_imc]
      type = TimeDerivative
      variable = eta_imc
    [../]
    [./ACBulkF_imc] # sum_j dh_j/deta_i*F_j+w*dg/deta_i, last term is not used
      type = KKSMultiACBulkF
      variable  = eta_imc
      Fj_names  = 'fch_cu fch_imc fch_sn'
      hj_names  = 'h_cu h_imc h_sn'
      gi_name   = g_imc
      eta_i     = eta_imc
      wi        = 1
      mob_name = L
      args      = 'c_cu c_imc c_sn eta_cu eta_sn '
    [../]
    [./ACBulkC_imc] # -L\sum_j dh_j/deta_i*mu_jc_j
      type = KKSMultiACBulkC
      variable  = eta_imc
      Fj_names  = 'fch_cu fch_imc fch_sn'
      hj_names  = 'h_cu h_imc h_sn'
      cj_names  = 'c_cu c_imc c_sn'
      eta_i     = eta_imc
      mob_name = L
      args      = 'eta_cu eta_sn '
    [../]
    [./ACInterface_imc] # L*kappa*grad\eta_i
      type = ACInterface
      variable = eta_imc
      kappa_name = kappa
      mob_name = L
      args      = 'eta_cu eta_sn'
      variable_L = true
    [../]
    [./ACdfintdeta_imc]
      type = ACGrGrMulti
      variable = eta_imc
      v = 'eta_cu eta_sn'
      gamma_names = 'gamma gamma'
      mob_name = L
      args = 'eta_cu eta_sn'
    [../]

    #Kernels for Allen-Cahn equation for Sn
    [./detadt_sn]
      type = TimeDerivative
      variable = eta_sn
    [../]
    [./ACBulkF_sn] # sum_j dh_j/deta_i*F_j+w*dg/deta_i, last term is not used
      type = KKSMultiACBulkF
      variable  = eta_sn
      Fj_names  = 'fch_cu fch_imc fch_sn'
      hj_names  = 'h_cu h_imc h_sn'
      gi_name   = g_sn
      eta_i     = eta_sn
      wi        = 1
      mob_name = L
      args      = 'c_cu c_imc c_sn eta_imc eta_cu '
    [../]
    [./ACBulkC_sn] # -L\sum_j dh_j/deta_i*mu_jc_j
      type = KKSMultiACBulkC
      variable  = eta_sn
      Fj_names  = 'fch_cu fch_imc fch_sn'
      hj_names  = 'h_cu h_imc h_sn'
      cj_names  = 'c_cu c_imc c_sn'
      eta_i     = eta_sn
      mob_name = L
      args      = 'eta_cu eta_imc '
    [../]
    [./ACInterface_sn] # L*kappa*grad\eta_i
      type = ACInterface
      variable = eta_sn
      kappa_name = kappa
      mob_name = L
      args      = 'eta_cu eta_imc'
      variable_L = true
    [../]
    [./ACdfintdeta_sn]
      type = ACGrGrMulti
      variable = eta_sn
      v = 'eta_cu eta_imc'
      gamma_names = 'gamma gamma'
      mob_name = L
      args= 'eta_cu eta_imc'
    [../]
 # Kernel for thermal conduction
#[./Laplacian]
    #type = MatDiffusion
    #variable = temp
    #D_name = thermcond # thermal_conductivity name in Derivative Parsed Material parser , sigma_el(eta_i)
    #args = 'eta_cu eta_imc eta_sn ' #added after a warning
  #[../]

[]

[AuxVariables]
    [./f_density] #local free energy density
      order = CONSTANT
      family = MONOMIAL
    [../]
    [./f_int]
        order = CONSTANT
        family = MONOMIAL
    [../]
[]

[AuxKernels]
    [./f_density]
        type = KKSMultiFreeEnergy
        variable = f_density
        hj_names = 'h_cu h_imc h_sn'
        Fj_names = 'fch_cu fch_imc fch_sn'
        gj_names = 'g_cu g_imc g_sn'
        additional_free_energy = f_int
        interfacial_vars = 'eta_cu eta_imc eta_sn'
        kappa_names = 'kappa kappa kappa'
        w = 1
    [../]
    [./f_int]
        type = ParsedAux
        variable = f_int
        args = 'eta_cu eta_imc eta_sn'
        constant_names = 'gamma mu'
        constant_expressions = '0.5 1.'
        function = 'mu*(0.25*eta_cu^4-0.5*eta_cu^2+0.25*eta_imc^4-0.5*eta_imc^2+0.25*eta_sn^4-0.5*eta_sn^2+gamma*(eta_cu^2*(eta_imc^2+eta_sn^2)+eta_imc^2*eta_sn^2))+0.25'
    [../]
[]
[Postprocessors]
    [./imc_thickness]
        type = NodalSum
        execute_on = timestep_end
        variable = eta_imc
    [../]
    [./total_energy]
        type = ElementIntegralVariablePostprocessor
        variable = f_density
        execute_on = TIMESTEP_END
    [../]
[]
[Executioner]
  type = Transient
  scheme = bdf2
  solve_type = 'PJFNK'
  #########PETSC_OPTIONS###################very_important###################
  petsc_options_iname = '-pc_type -sub_pc_type   -sub_pc_factor_shift_type'
  petsc_options_value = 'asm       ilu            nonzero'
  #solve_type =Newton
  l_max_its = 50
  l_tol = 1e-4
  nl_max_its = 20
  nl_rel_tol = 1e-10
  nl_abs_tol = 1e-10
   # nl_rel_tol = 1e-10 # 1e-08 #1e-10 #1.0e-10
   #  nl_abs_tol = 1e-11 # 1e-09 #1e-11 #1.0e-10
    #dt=0.0005
    #dt=0.05
    #end_time = 60 #400
     #dt=1.00E+06 #100 ns 10 second is the diffusion time scale, and so timestep kept greater than 10 ns
     #end_time=6.00E+11 #1.00E+08 = 1000 ns; 600 s = total time 1.0E+12 = 1000 s
[./TimeStepper]
    ## Turn on time stepping
    type = IterationAdaptiveDT
    dt = 1.00E+04 #06
    cutback_factor = 0.8
    growth_factor = 2.0 #1.5
    optimal_iterations = 7
    end_time = 2.00E+13
 [../]
 # adaptive mesh to resolve an interface
   [./Adaptivity]
     initial_adaptivity    = 3 #3 #2             # Number of times mesh is adapted to initial condition
     refine_fraction       = 0.7           # Fraction of high error that will be refined
     coarsen_fraction      = 0.1           # Fraction of low error that will coarsened
     max_h_level           = 2 #3             # Max number of refinements used, starting from initial mesh (before uniform refinement)
     weight_names          = 'eta_cu eta_imc eta_sn'
     weight_values         = '1 1 1  '
   [../]
[]

[Preconditioning]
  active = 'full'
  [./full]
    type = SMP
    full = true
  [../]
  [./mydebug]
    type = FDP
    full = true
  [../]
[]

#[Outputs]
#  exodus = true
#  csv = true
#[]

[Outputs]
  exodus = true
  csv = true
  #interval=25
  #interval=30
  interval=100 #50 #0
  #interval=5 #5 #20
  #interval =1000 #1000 #100000000000 #5 0.1 ns
  #execute_on = 'TIMESTEP_END'
  #[./other]        # creates input_other.e output every 30 timestep
     #type = Exodus
    # interval =30 # 1 
  #[../]
  #to recover the simulation using checkpoints
  [./my_checkpoint]
    type = Checkpoint
    num_files = 4
    interval = 300 #5
  [../]
[]


[Debug]
  show_var_residual_norms = true
[]
