    // Solve the momentum equation
    fvVectorMatrix UEqn(
		(nonlinear ? fvm::ddt(U) + fvm::div(phi, U) : fvm::ddt(U))
	      + turbulence->divDevReff(U)
	     ==
		fvOptions(U)
    );


    UEqn.relax();

    fvOptions.constrain(UEqn);

    if (pimple.momentumPredictor())
    {
        solve
        (
            UEqn
         ==
	  - fvc::grad(p_rgh)
          + g*rhok_tag
        );

        fvOptions.correct(U);
    }


