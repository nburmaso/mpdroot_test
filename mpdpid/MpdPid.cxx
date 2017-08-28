#include "MpdPid.h"

MpdPid::MpdPid() : TObject(){

      parElBB = 0;
      parPiBB = 0;
      parKaBB = 0;
      parPrBB = 0;
      parDeBB = 0;
      parTrBB = 0;
      parHe3BB = 0;
      parHe4BB = 0;
      fProbEl = 0.;
      fProbPi = 0.;
      fProbKa = 0.;
      fProbPr = 0.;
      fProbDe = 0.;
      fProbTr = 0.;
      fProbHe3 = 0.;
      fProbHe4 = 0.;
      fCharge = 1;
      fEnergy = 4.;
      fTracking = kTRUE;
}


MpdPid::MpdPid(Double_t sigmaTof, Double_t sigmaEloss, Double_t sqrts, Double_t koef, TString Generator, TString Tracking, TString NSigPart)
   : TObject(), kSigmaTof(sigmaTof), kSigmaEloss(sigmaEloss), fCharge(1), fKoef(koef),
     fEnergy(sqrts) 
{
	Init(Generator, Tracking, NSigPart);
}

Double_t MpdPid::GetDedxWidthValue(Double_t p, Int_t specie)
{
	/// Species: 1 - pions, 2 - kaons, 3 - protons, 4 - electrons, 5 - muons, 6 - deuterons, 7 - tritons, 8 - He3, 9 - He4
	Double_t WidthValue = 0.;
	if (specie == 1)
	{
		if (p < piSigmaLowP->GetXmax()) WidthValue = piSigmaLowP->Eval(p);
		if ((p >= piSigmaMidP->GetXmin()) && (p < piSigmaMidP->GetXmax())) WidthValue = piSigmaMidP->Eval(p);
		if ((p >= piSigmaHighP->GetXmin()) && (p <= piSigmaHighP->GetXmax())) WidthValue = piSigmaHighP->Eval(p);
	}
	if (specie == 2)
	{
		if (p < kaSigmaLowP->GetXmax()) WidthValue = kaSigmaLowP->Eval(p);
		if ((p >= kaSigmaHighP->GetXmin()) && (p <= kaSigmaHighP->GetXmax())) WidthValue = kaSigmaHighP->Eval(p);
	}
	if (specie == 3)
	{
		if (p < prSigmaLowP->GetXmax()) WidthValue = prSigmaLowP->Eval(p);
		if ((p >= prSigmaHighP->GetXmin()) && (p <= prSigmaHighP->GetXmax())) WidthValue = prSigmaHighP->Eval(p);
	}
	if (specie == 4)
	{
		if (p < elSigmaLowP->GetXmax()) WidthValue = elSigmaLowP->Eval(p);
		if ((p >= elSigmaMidP->GetXmin()) && (p <= elSigmaMidP->GetXmax())) WidthValue = elSigmaMidP->Eval(p);
		if ((p >= elSigmaHighP->GetXmin()) && (p <= elSigmaHighP->GetXmax())) WidthValue = elSigmaHighP->Eval(p);
	}
	if (specie == 5)
	{
		if (p < muSigmaLowP->GetXmax()) WidthValue = muSigmaLowP->Eval(p);
		if ((p >= muSigmaMidP->GetXmin()) && (p <= muSigmaMidP->GetXmax())) WidthValue = muSigmaMidP->Eval(p);
		if ((p >= muSigmaHighP->GetXmin()) && (p <= muSigmaHighP->GetXmax())) WidthValue = muSigmaHighP->Eval(p);
	}
	
	return WidthValue;
}

Double_t MpdPid::GetTailValue(Double_t p, Int_t specie)
{
	/// Species: 1 - pions, 2 - kaons, 3 - protons, 4 - electrons, 5 - muons, 6 - deuterons, 7 - tritons, 8 - He3, 9 - He4
	Double_t TailValue = 0.;
	
	if (specie == 1)
	{
		if (p < fAsymmetryPiLowP->GetXmax()) TailValue = fAsymmetryPiLowP->Eval(p);
		if ( (p >= fAsymmetryPiMidP->GetXmin()) && (p < fAsymmetryPiMidP->GetXmax()) ) TailValue = fAsymmetryPiMidP->Eval(p);
		if ( (p >= fAsymmetryPiHighP->GetXmin()) && (p <= fAsymmetryPiHighP->GetXmax()) ) TailValue = fAsymmetryPiHighP->Eval(p);
	}
	if (specie == 2)
	{
		if (p < fAsymmetryKaLowP->GetXmax()) TailValue = fAsymmetryKaLowP->Eval(p);
		if ( (p >= fAsymmetryKaMidP->GetXmin()) && (p < fAsymmetryKaMidP->GetXmax()) ) TailValue = fAsymmetryKaMidP->Eval(p);
		if ( (p >= fAsymmetryKaHighP->GetXmin()) && (p <= fAsymmetryKaHighP->GetXmax()) ) TailValue = fAsymmetryKaHighP->Eval(p);
	}
	if (specie == 3)
	{
		if (p < fAsymmetryPrLowP->GetXmax()) TailValue = fAsymmetryPrLowP->Eval(p);
		if ( (p >= fAsymmetryPrMidP->GetXmin()) && (p < fAsymmetryPrMidP->GetXmax()) ) TailValue = fAsymmetryPrMidP->Eval(p);
		if ( (p >= fAsymmetryPrHighP->GetXmin()) && (p <= fAsymmetryPrHighP->GetXmax()) ) TailValue = fAsymmetryPrHighP->Eval(p);
	}
	if (specie == 4)
	{
		if (p < fAsymmetryElLowP->GetXmax()) TailValue = fAsymmetryElLowP->Eval(p);
		if ( (p >= fAsymmetryElMidP->GetXmin()) && (p < fAsymmetryElMidP->GetXmax()) ) TailValue = fAsymmetryElMidP->Eval(p);
		if ( (p >= fAsymmetryElHighP->GetXmin()) && (p <= fAsymmetryElHighP->GetXmax()) ) TailValue = fAsymmetryElHighP->Eval(p);
	}
	if (specie == 5)
	{
		if (p < fAsymmetryMuLowP->GetXmax()) TailValue = fAsymmetryMuLowP->Eval(p);
		if ( (p >= fAsymmetryMuMidP->GetXmin()) && (p < fAsymmetryMuMidP->GetXmax()) ) TailValue = fAsymmetryMuMidP->Eval(p);
		if ( (p >= fAsymmetryMuHighP->GetXmin()) && (p <= fAsymmetryMuHighP->GetXmax()) ) TailValue = fAsymmetryMuHighP->Eval(p);
	}
	
	return TailValue;
}

Double_t MpdPid::GetDedxProb_asym(Double_t cut, Double_t p, Double_t dedx, Double_t n, Double_t emean, Double_t sige, Int_t specie)
{
	Double_t fProb = 0.;
	Double_t delta = GetTailValue(p, specie);
	Double_t SideOfAsymmetry = delta * (dedx - emean);
	if (SideOfAsymmetry >= 0.) cut *= 1. + TMath::Abs(delta);
	if (TMath::Abs((dedx/emean-1.)/sige) < cut)
	{
		fasymgaus->SetParameters(n, 1., sige, delta);
		fProb = fasymgaus->Eval(dedx/emean);
	}
	return fProb;
}

Double_t MpdPid::GetCombProb_asym(Double_t cut_dedx, Double_t cut_m2, Double_t p, Double_t dedx, Double_t m2, Double_t n, Double_t emean, Double_t mmean, Double_t sige, Double_t sigm, Int_t specie)
{
	Double_t fProb = 0., xx, yy;
	xx = (dedx/emean-1.)/sige;
    yy = (m2-mmean)/sigm;
	Double_t delta = GetTailValue(p, specie);
	Double_t SideOfAsymmetry = delta * (dedx - emean);
	if (SideOfAsymmetry >= 0.) xx /= 1. + TMath::Abs(delta);
	if ( (TMath::Abs(xx) < cut_dedx) && (TMath::Abs(yy) < cut_m2) )
	{
		fasymgaus2->SetParameters(n, 1., sige, delta, mmean, sigm);
		fProb = fasymgaus2->Eval(dedx/emean, m2);
	}
	return fProb;
}

/// Sum of two exponents in total momentum (pions and electrons)
Double_t MpdPid::MomPi(Double_t *x, Double_t *par)
{
  Double_t p = x[0], xx, x1, x2;
  xx=sqrt(p*p+par[4]*par[4])-par[4];
  x1=(1+par[1])/(par[2]*(par[4]+par[2]))/exp(xx/par[2]);
  x2=par[1]/(par[3]*(par[4]+par[3]))/exp(xx/par[3]);
  
  return (par[0]*p*(x1+x2));    
}

/// Difference of 2 exponents in total momentum (All specie, except pi's and e+/-)
Double_t MpdPid::MomPr(Double_t *x, Double_t *par)
{
  Double_t p = x[0], xx, x1, x2;
  xx=sqrt(p*p+par[4]*par[4])-par[4];
  x1=(1+par[1])/(par[2]*(par[4]+par[2]))/exp(xx/par[2]);
  x2=par[1]/(par[3]*(par[4]+par[3]))/exp(xx/par[3]);
  
  return (par[0]*p*(x1-x2));
}

Double_t MpdPid::AsymGaus(Double_t *x, Double_t *par)
{
	Double_t peak = par[1];
	if (x[0] < peak)
	return par[0]*TMath::Exp( -0.5 * TMath::Power( ( (x[0] - par[1]) / par[2] ), 2 ));
	else
	return par[0]*TMath::Exp( -0.5 * TMath::Power( ( (x[0] - par[1]) / ((1. + par[3]) * par[2]) ), 2 ));
}

Double_t MpdPid::AsymGaus2(Double_t *x, Double_t *par)
{
	Double_t peak = par[1];
	if (x[0] < peak)
	return par[0]*TMath::Exp( -0.5 * TMath::Power( ( (x[0] - par[1]) / par[2] ), 2 )) * TMath::Exp( -0.5 * TMath::Power( ( (x[1] - par[4]) / par[5] ), 2 ));
	else
	return par[0]*TMath::Exp( -0.5 * TMath::Power( ( (x[0] - par[1]) / ((1. + par[3]) * par[2]) ), 2 )) * TMath::Exp( -0.5 * TMath::Power( ( (x[1] - par[4]) / par[5] ), 2 ));
}

void MpdPid::Init(TString Generator, TString Tracking, TString NSigPart)
{
	cout<<"MpdPid::Init().."<<endl;
	
	fSigmaDedx_2 = 0.11; fSigmaDedx_3 = 0.08;
	Double_t PMIN=0., PMAX=3.0;
	Double_t dedxParam;
	
	/// Setting default ratio ('rat' is pos./neg.)
	prrat=43.43;
	if (fEnergy < 7.0) prrat=1000.;
	
	///
	/// Bethe-Bloch versus p (MC with STRA=0!)
	///
	
	parElBB=new TF1("parElBB","[0]/x+[1]",PMIN,PMAX);
	parMuBB = new TF1("parMuBB","[0]/pow(x/sqrt(x*x+0.011),[3])*([1]-pow(x/sqrt(x*x+0.011),[3])-log([2]+pow(1./(x/0.1057),[4])) )",PMIN,PMAX);
	parPiBB = new TF1("parPiBB","[0]/pow(x/sqrt(x*x+0.01949),[3])*([1]-pow(x/sqrt(x*x+0.01949),[3])-log([2]+pow(1./(x/0.1396),[4])) )",PMIN,PMAX);
	parKaBB = new TF1("parKaBB","[0]/pow(x/sqrt(x*x+0.2437),[3])*([1]-pow(x/sqrt(x*x+0.2437),[3])-log([2]+pow(1./(x/0.4937),[4])) )",PMIN,PMAX);
	parPrBB = new TF1("parPrBB","[0]/pow(x/sqrt(x*x+0.88),[3])*([1]-pow(x/sqrt(x*x+0.88),[3])-log([2]+pow(1./(x/0.9383),[4])) )",PMIN,PMAX);
	parDeBB = new TF1("parDeBB","[0]/pow(x/sqrt(x*x+3.52),[3])*([1]-pow(x/sqrt(x*x+3.52),[3])-log([2]+pow(1./(x/1.876),[4])) )",PMIN,PMAX);
	parTrBB = new TF1("parTrBB","[0]/pow(x/sqrt(x*x+7.89),[3])*([1]-pow(x/sqrt(x*x+7.89),[3])-log([2]+pow(1./(x/2.81),[4])) )",PMIN,PMAX);
	/// Double charged have p_reco= p_MC/2
	parHe3BB = new TF1("parHe3BB","[0]*((1+(x/1.4047)**2)/pow(x/1.4047,[3])*([1]+[2]*log(1+pow(x/1.4047,2)))-1.)",PMIN,PMAX);
	parHe4BB = new TF1("parHe4BB","[0]*((1+(x/1.863)**2)/pow(x/1.863,[3])*([1]+[2]*log(1+pow(x/1.863,2)))-1.)",PMIN,PMAX);
	
	///
	/// Width of mass-squared versus total p
	///
	
	parElM2=new TF1("parElM2","pol2(0)",PMIN,PMAX);  
	parMuM2=new TF1("parMuM2","pol2(0)",PMIN,PMAX);  
	parPiLowPM2=new TF1("parPiLowPM2","pol2(0)",PMIN,PMAX);  
	parPiHighPM2=new TF1("parPiHighPM2","pol2(0)",PMIN,PMAX);  
	parKaM2=new TF1("parKaM2","pol2(0)",PMIN,PMAX);
	parPrLowPM2=new TF1("parPrLowPM2","pol3(0)",PMIN,PMAX);  
	parPrHighPM2=new TF1("parPrHighPM2","pol2(0)",PMIN,PMAX);  
	parDeM2=new TF1("parDeM2","pol3(0)",PMIN,PMAX);  
	parTrM2=new TF1("parTrM2","pol3(0)",PMIN,PMAX);  
	parHe3M2=new TF1("parHe3M2","pol3(0)",PMIN,PMAX);  
	parHe4M2=new TF1("parHe4M2","pol3(0)",PMIN,PMAX);  
	
	/// DEFINE TRACKING
	if(Tracking=="HP")
	{
		fSigmaDedx_1 = 0.05;
		fTracking = kFALSE;
		
		/// electrons
		dedxParam = fKoef*(-8.27289e-09); parElBB->SetParameter(0, dedxParam);
		dedxParam = fKoef*(2.10438e-06); parElBB->SetParameter(1, dedxParam);
		/// muons
		dedxParam = fKoef*2.56183e-06;
		parMuBB->SetParameters(dedxParam,2.7034,2.52734,0.854563,0.330576);
		/// pions
		dedxParam = fKoef*(-1.19342e-07);
		parPiBB->SetParameters(dedxParam,-7.83114,8.17749,1.85775,-1.80695);
		/// kaons
		dedxParam = fKoef*6.50167e-07;
		parKaBB->SetParameters(dedxParam,1.01718,-0.795357,1.80916,0.0707667);
		/// protons
		dedxParam = fKoef*(4.40008e-07);
		parPrBB->SetParameters(dedxParam,2.97563,-0.192657,2.16118,0.61451);
		/// deuterons
		dedxParam = fKoef*3.27e-07;
		parDeBB->SetParameters(dedxParam,3.74,-0.23,2.32,0.987);
		/// tritons
		dedxParam = fKoef*2.59e-07;
		parTrBB->SetParameters(dedxParam,5.06,0.0001,2.2,1.056);
		/// He3
		dedxParam = fKoef*2.86201e-06;
		parHe3BB->SetParameters(dedxParam,2.10168e+00,2.74807e-01,1.86774e+00);
		/// He4
		dedxParam = fKoef*2.96e-06;
		parHe4BB->SetParameters(dedxParam,2.085,0.256,1.85);
		
		/// m2
		parElM2->SetParameters(0.00102552,-0.000243946,0.0307395);
		parMuM2->SetParameters(0.00155957,-0.000984273,0.0306857);
		parPiLowPM2->SetParameters(0.00259115, -0.00251021, 0.0287287);
		parPiHighPM2->SetParameters(-0.0393955, 0.0586315, 0.00516675);
		parKaM2->SetParameters(0.00144014, 0.0183536, 0.0161613);
		parPrLowPM2->SetParameters(0.0777042, -0.123828, 0.139278, -0.0338542);
		parPrHighPM2->SetParameters(0.0244298, 0.018534, 0.0174998);
		parDeM2->SetParameters(0.535691,-0.529882,0.293807,-0.0428139);
		parTrM2->SetParameters(0.422,0.3,-0.202,0.0524);
		parHe3M2->SetParameters(0.17,-0.0,0.0,-0.00);
		parHe4M2->SetParameters(0.3,-0.0,0.0,-0.00);
		
		/// dE/dx width
		elSigmaLowP = new TF1("elSigmaLowP", "pol1(0)", 0., 0.55); elSigmaLowP->SetParameters(0.0484732, -0.002846727);
		elSigmaMidP = new TF1("elSigmaMidP", "pol1(0)", 0.55, 2.0); elSigmaMidP->SetParameters(0.0470012, -0.000170422);
		elSigmaHighP = new TF1("elSigmaHighP", "pol1(0)", 2.0, 3.0); elSigmaHighP->SetParameters(0.0477092, -0.000503717);
		muSigmaLowP = new TF1("muSigmaLowP", "pol1(0)", 0., 0.3); muSigmaLowP->SetParameters(0.0668409, -0.0657125);
		muSigmaMidP = new TF1("muSigmaMidP", "pol1(0)", 0.3, 1.05); muSigmaMidP->SetParameters(0.0458461, 0.00145295);
		muSigmaHighP = new TF1("muSigmaHighP", "pol1(0)", 1.05, 3.0); muSigmaHighP->SetParameters(0.0450895, 0.00118004);
		piSigmaLowP = new TF1("piSigmaLowP", "pol1(0)", 0., 0.35); piSigmaLowP->SetParameters(0.0787807, -0.100463);
		piSigmaMidP = new TF1("piSigmaMidP", "pol1(0)", 0.35, 1.5); piSigmaMidP->SetParameters(0.0487635, 0.000857375);
		piSigmaHighP = new TF1("piSigmaHighP", "pol1(0)", 1.5, 3.0); piSigmaHighP->SetParameters(0.0443209, 0.00524245);
		prSigmaLowP = new TF1("prSigmaLowP", "pol1(0)", 0., 0.2); prSigmaLowP->SetParameters(0.068647, -0.0426204);
		prSigmaHighP = new TF1("prSigmaHighP", "pol1(0)", 0.2, 3.0); prSigmaHighP->SetParameters(0.0476193, -0.000557916);
		kaSigmaLowP = new TF1("kaSigmaLowP", "pol1(0)", 0., 0.2); kaSigmaLowP->SetParameters(0.149889, -0.465214);
		kaSigmaHighP = new TF1("kaSigmaHighP", "pol1(0)", 0.2, 3.0); kaSigmaHighP->SetParameters(0.0486608, -0.000571203);
		
		/// Asymmetry
		fAsymmetryElLowP = new TF1("fAsymmetryElLowP", "pol1(0)", 0., 0.5); fAsymmetryElLowP->SetParameters(0.456871, -0.0424708);
		fAsymmetryElMidP = new TF1("fAsymmetryElMidP", "pol1(0)", 0.5, 0.85); fAsymmetryElMidP->SetParameters(0.4418036, -0.0131662);
		fAsymmetryElHighP = new TF1("fAsymmetryElHighP", "pol1(0)", 0.85, 3.0); fAsymmetryElHighP->SetParameters(0.440012, -0.0113746);
		fAsymmetryMuLowP = new TF1("fAsymmetryMuLowP", "pol1(0)", 0., 0.175); fAsymmetryMuLowP->SetParameters(12.138, -66.6292);
		fAsymmetryMuMidP = new TF1("fAsymmetryMuMidP", "pol1(0)", 0.175, 0.65); fAsymmetryMuMidP->SetParameters(0.31412, 0.158834);
		fAsymmetryMuHighP = new TF1("fAsymmetryMuHighP", "pol1(0)", 0.65, 3.0); fAsymmetryMuHighP->SetParameters(0.409629, -0.0234975);
		fAsymmetryPiLowP = new TF1("fAsymmetryPiLowP", "pol1(0)", 0., 0.18); fAsymmetryPiLowP->SetParameters(11.3953, -58.1321);
		fAsymmetryPiMidP = new TF1("fAsymmetryPiMidP", "pol1(0)", 0.18, 0.9); fAsymmetryPiMidP->SetParameters(0.412467, -0.0289088);
		fAsymmetryPiHighP = new TF1("fAsymmetryPiHighP", "pol1(0)", 0.9, 3.); fAsymmetryPiHighP->SetParameters(0.408242, -0.0520603);
		fAsymmetryPrLowP = new TF1("fAsymmetryPrLowP", "pol1(0)", 0., 0.3); fAsymmetryPrLowP->SetParameters(6.40228, -19.5847);
		fAsymmetryPrMidP = new TF1("fAsymmetryPrMidP", "pol1(0)", 0.3, 1.0); fAsymmetryPrMidP->SetParameters(0.193311, 0.179621);
		fAsymmetryPrHighP = new TF1("fAsymmetryPrHighP", "pol1(0)", 1.0, 3.); fAsymmetryPrHighP->SetParameters(0.21947, 0.0936557);
		fAsymmetryKaLowP = new TF1("fAsymmetryKaLowP", "pol1(0)", 0., 0.45); fAsymmetryKaLowP->SetParameters(3.21698, -6.37965);
		fAsymmetryKaMidP = new TF1("fAsymmetryKaMidP", "pol1(0)", 0.45, 1.05); fAsymmetryKaMidP->SetParameters(0.237053, 0.143231);
		fAsymmetryKaHighP = new TF1("fAsymmetryKaHighP", "pol1(0)", 1.05, 3.); fAsymmetryKaHighP->SetParameters(0.252239, 0.0558685);
	}
	else /// Tracking == "CF" is default
	{
		if (Tracking != "CF") cout << "ERROR! Unknown tracking method! Switch to default (\"CF\")." << endl;
		
		fSigmaDedx_1 = 0.07;
		fTracking = kTRUE;
		
		/// electrons
		dedxParam = fKoef*(-65.7432); parElBB->SetParameter(0, dedxParam);
		dedxParam = fKoef*4007.68; parElBB->SetParameter(1, dedxParam);
		/// muons
		dedxParam = fKoef*(-54.6053);
		parMuBB->SetParameters(dedxParam,-41.38,109.594,1.30576,-4.66578);
		/// pions
		dedxParam = fKoef*(-333.199);
		parPiBB->SetParameters(dedxParam,-4.76053,3.73173,1.82109,-1.2414);
		/// kaons
		dedxParam = fKoef*(-674.513);
		parKaBB->SetParameters(dedxParam,-4.02511,0.391596,0.993733,4.13295);
		/// protons
		dedxParam = fKoef*(-2328.44);
		parPrBB->SetParameters(dedxParam,-0.054584,1.15196,0.819829,2.74767);
		/// deuterons
		dedxParam = fKoef*3.27e-07;
		parDeBB->SetParameters(dedxParam,3.74,-0.23,2.32,0.987);
		/// tritons
		dedxParam = fKoef*2.59e-07;
		parTrBB->SetParameters(dedxParam,5.06,0.0001,2.2,1.056);
		/// He3
		dedxParam = fKoef*2.86201e-06;
		parHe3BB->SetParameters(dedxParam,2.10168e+00,2.74807e-01,1.86774e+00);
		/// He4
		dedxParam = fKoef*2.96e-06;
		parHe4BB->SetParameters(dedxParam,2.085,0.256,1.85);
		
		/// m2
		parElM2->SetParameters(0.001227,-0.000973509,0.0314155);
		parMuM2->SetParameters(0.00166279,-0.00131341,0.0311028);
		parPiLowPM2->SetParameters(0.00284467, -0.00307647, 0.0303474);
		parPiHighPM2->SetParameters(-0.0364446, 0.0569689, 0.00652391);
		parKaM2->SetParameters(-1.25162e-05, 0.0206642, 0.0187346);
		parPrLowPM2->SetParameters(0.0752714, -0.115864, 0.139697, -0.033123);
		parPrHighPM2->SetParameters(0.0130241, 0.0302837, 0.0207017);
		parDeM2->SetParameters(0.535691,-0.529882,0.293807,-0.0428139);
		parTrM2->SetParameters(0.422,0.3,-0.202,0.0524);
		parHe3M2->SetParameters(0.17,-0.0,0.0,-0.00);
		parHe4M2->SetParameters(0.3,-0.0,0.0,-0.00);
		
		/// dE/dx width
		elSigmaLowP = new TF1("elSigmaLowP", "pol1(0)", 0., 0.55); elSigmaLowP->SetParameters(0.0747217, -0.0308101);
		elSigmaMidP = new TF1("elSigmaMidP", "pol1(0)", 0.55, 2.0); elSigmaMidP->SetParameters(0.0653074, -0.00546004);
		elSigmaHighP = new TF1("elSigmaHighP", "pol1(0)", 2.0, 3.0); elSigmaHighP->SetParameters(0.0572145, -0.00104922);
		muSigmaLowP = new TF1("muSigmaLowP", "pol1(0)", 0., 0.3); muSigmaLowP->SetParameters(0.115611, -0.179933);
		muSigmaMidP = new TF1("muSigmaMidP", "pol1(0)", 0.3, 1.05); muSigmaMidP->SetParameters(0.0583018, 0.00140717);
		muSigmaHighP = new TF1("muSigmaHighP", "pol1(0)", 1.05, 3.0); muSigmaHighP->SetParameters(0.0570477, -8.02801e-05);
		piSigmaLowP = new TF1("piSigmaLowP", "pol1(0)", 0., 0.25); piSigmaLowP->SetParameters(0.144972, -0.308612);
		piSigmaMidP = new TF1("piSigmaMidP", "pol1(0)", 0.25, 0.4); piSigmaMidP->SetParameters(0.0805, -0.0553436);
		piSigmaHighP = new TF1("piSigmaHighP", "pol1(0)", 0.4, 3.0); piSigmaHighP->SetParameters(0.0587877, 0.00143879);
		prSigmaLowP = new TF1("prSigmaLowP", "pol1(0)", 0., 0.2); prSigmaLowP->SetParameters(0.157451, -0.481992);
		prSigmaHighP = new TF1("prSigmaHighP", "pol1(0)", 0.2, 3.0); prSigmaHighP->SetParameters(0.0623534, 0.00287991);
		kaSigmaLowP = new TF1("kaSigmaLowP", "pol1(0)", 0., 0.2); kaSigmaLowP->SetParameters(0.120409, -0.289855);
		kaSigmaHighP = new TF1("kaSigmaHighP", "pol1(0)", 0.2, 3.0); kaSigmaHighP->SetParameters(0.0630206, -0.00374603);
		
		/// Asymmetry
		fAsymmetryElLowP = new TF1("fAsymmetryElLowP", "pol1(0)", 0., 0.5); fAsymmetryElLowP->SetParameters(-0.340074, 1.04407);
		fAsymmetryElMidP = new TF1("fAsymmetryElMidP", "pol1(0)", 0.5, 0.85); fAsymmetryElMidP->SetParameters(0.291559, -0.306138);
		fAsymmetryElHighP = new TF1("fAsymmetryElHighP", "pol1(0)", 0.85, 3.0); fAsymmetryElHighP->SetParameters(0.0915437, 0.0467649);
		fAsymmetryMuLowP = new TF1("fAsymmetryMuLowP", "pol1(0)", 0., 0.125); fAsymmetryMuLowP->SetParameters(2.5656, -14.391);
		fAsymmetryMuMidP = new TF1("fAsymmetryMuMidP", "pol1(0)", 0.125, 0.5); fAsymmetryMuMidP->SetParameters(-0.0467746, 0.496758);
		fAsymmetryMuHighP = new TF1("fAsymmetryMuHighP", "pol1(0)", 0.5, 3.0); fAsymmetryMuHighP->SetParameters(0.196422, 0.0117276);
		fAsymmetryPiLowP = new TF1("fAsymmetryPiLowP", "pol1(0)", 0., 0.18); fAsymmetryPiLowP->SetParameters(3.50026, -18.1992);
		fAsymmetryPiMidP = new TF1("fAsymmetryPiMidP", "pol1(0)", 0.18, 0.9); fAsymmetryPiMidP->SetParameters(0.106035, 0.237438);
		fAsymmetryPiHighP = new TF1("fAsymmetryPiHighP", "pol1(0)", 0.9, 3.); fAsymmetryPiHighP->SetParameters(0.256077, -0.0069969);
		fAsymmetryPrLowP = new TF1("fAsymmetryPrLowP", "pol1(0)", 0., 0.25); fAsymmetryPrLowP->SetParameters(1.68519, -2.75816);
		fAsymmetryPrMidP = new TF1("fAsymmetryPrMidP", "pol1(0)", 0.25, 0.5); fAsymmetryPrMidP->SetParameters(1.68519, -2.75816);
		fAsymmetryPrHighP = new TF1("fAsymmetryPrHighP", "pol1(0)", 0.5, 3.); fAsymmetryPrHighP->SetParameters(-0.0761382, 0.186669);
		fAsymmetryKaLowP = new TF1("fAsymmetryKaLowP", "pol1(0)", 0., 0.5); fAsymmetryKaLowP->SetParameters(2.3588, -4.87114);
		fAsymmetryKaMidP = new TF1("fAsymmetryKaMidP", "pol1(0)", 0.5, 1.05); fAsymmetryKaMidP->SetParameters(0.00526557, 0.239378);
		fAsymmetryKaHighP = new TF1("fAsymmetryKaHighP", "pol1(0)", 1.05, 3.); fAsymmetryKaHighP->SetParameters(0.0892569, 0.119403);
	}
	
	/// Particle yields versus momentum (close to a thermal function).
	/// The predicted number roughly speaking are not dN/dy or total yiels,
	/// only their relative hights are of relevance!
	
	Double_t amplParam;
	if (Generator != "NSIG")
	{
		parElPosMom = new TF1("parElPosMom",this,&MpdPid::MomPr,PMIN,PMAX,5,"MpdPid","MomPi");
		parElNegMom = new TF1("parElNegMom",this,&MpdPid::MomPr,PMIN,PMAX,5,"MpdPid","MomPi");
		parMuPosMom = new TF1("parMuPosMom",this,&MpdPid::MomPi,PMIN,PMAX,5,"MpdPid","MomPi");
		parMuNegMom = new TF1("parMuNegMom",this,&MpdPid::MomPi,PMIN,PMAX,5,"MpdPid","MomPi");
		parPiPosMom = new TF1("parPiPosMom",this,&MpdPid::MomPi,PMIN,PMAX,5,"MpdPid","MomPi");
		parPiNegMom = new TF1("parPiNegMom",this,&MpdPid::MomPi,PMIN,PMAX,5,"MpdPid","MomPi");
		parKaPosMom = new TF1("parKaPosMom",this,&MpdPid::MomPr,PMIN,PMAX,5,"MpdPid","MomPr");
		parKaNegMom = new TF1("parKaNegMom",this,&MpdPid::MomPr,PMIN,PMAX,5,"MpdPid","MomPr");
		parPrPosMom = new TF1("parPrPosMom",this,&MpdPid::MomPr,PMIN,PMAX,5,"MpdPid","MomPr");
		parPrNegMom = new TF1("parPrNegMom",this,&MpdPid::MomPr,PMIN,PMAX,5,"MpdPid","MomPr");
		parDeMom = new TF1("parDeMom",this,&MpdPid::MomPr,PMIN,PMAX,5,"MpdPid","MomPr");
		parTrMom = new TF1("parTrMom",this,&MpdPid::MomPr,PMIN,PMAX,5,"MpdPid","MomPr");
		parHe3Mom = new TF1("parHe3Mom",this,&MpdPid::MomPr,PMIN,PMAX,5,"MpdPid","MomPr");
		parHe4Mom = new TF1("parHe4Mom",this,&MpdPid::MomPr,PMIN,PMAX,5,"MpdPid","MomPr");
	}
	else
	{
		if (NSigPart.Contains("el")) {parElPosMom = new TF1("parElPosMom","1.",PMIN,PMAX); parElNegMom = new TF1("parElNegMom","1.",PMIN,PMAX); cout << "electrons are included in n-sigma method..." << endl;}
		else {parElPosMom = new TF1("parElPosMom","0.",PMIN,PMAX); parElNegMom = new TF1("parElNegMom","0.",PMIN,PMAX);}
		if (NSigPart.Contains("mu")) {parMuPosMom = new TF1("parMuPosMom","1.",PMIN,PMAX); parMuNegMom = new TF1("parMuNegMom","1.",PMIN,PMAX); cout << "muons are included in n-sigma method..." << endl;}
		else {parMuPosMom = new TF1("parMuPosMom","0.",PMIN,PMAX); parMuNegMom = new TF1("parMuNegMom","0.",PMIN,PMAX);}
		if (NSigPart.Contains("pi")) {parPiPosMom = new TF1("parPiPosMom","1.",PMIN,PMAX); parPiNegMom = new TF1("parPiNegMom","1.",PMIN,PMAX); cout << "pions are included in n-sigma method..." << endl;}
		else {parPiPosMom = new TF1("parPiPosMom","0.",PMIN,PMAX); parPiNegMom = new TF1("parPiNegMom","0.",PMIN,PMAX);}
		if (NSigPart.Contains("ka")) {parKaPosMom = new TF1("parKaPosMom","1.",PMIN,PMAX); parKaNegMom = new TF1("parKaNegMom","1.",PMIN,PMAX); cout << "kaons are included in n-sigma method..." << endl;}
		else {parKaPosMom = new TF1("parKaPosMom","0.",PMIN,PMAX); parKaNegMom = new TF1("parKaNegMom","0.",PMIN,PMAX);}
		if (NSigPart.Contains("pr")) {parPrPosMom = new TF1("parPrPosMom","1.",PMIN,PMAX); parPrNegMom = new TF1("parPrNegMom","1.",PMIN,PMAX); cout << "protons are included in n-sigma method..." << endl;}
		else {parPrPosMom = new TF1("parPrPosMom","0.",PMIN,PMAX); parPrNegMom = new TF1("parPrNegMom","0.",PMIN,PMAX);}
		if (NSigPart.Contains("de")) {parDeMom = new TF1("parDeMom","1.",PMIN,PMAX); cout << "deuterons are included in n-sigma method..." << endl;}
		else parDeMom = new TF1("parDeMom","0.",PMIN,PMAX);
		if (NSigPart.Contains("tr")) {parTrMom = new TF1("parTrMom","1.",PMIN,PMAX); cout << "tritons are included in n-sigma method..." << endl;}
		else parTrMom = new TF1("parTrMom","0.",PMIN,PMAX);
		if (NSigPart.Contains("he3")) {parHe3Mom = new TF1("parHe3Mom","1.",PMIN,PMAX); cout << "he3 are included in n-sigma method..." << endl;}
		else parHe3Mom = new TF1("parHe3Mom","0.",PMIN,PMAX);
		if (NSigPart.Contains("he4")) {parHe4Mom = new TF1("parHe4Mom","1.",PMIN,PMAX); cout << "he4 are included in n-sigma method..." << endl;}
		else parHe4Mom = new TF1("parHe4Mom","0.",PMIN,PMAX);
	}
	
	for (Int_t itr = 0; itr < 14; itr++) Multiplicities[itr] = 0;
	if ( !( (Generator == "LAQGSM") || (Generator == "QGSM") || (Generator == "URQMD") || (Generator == "NSIG") ) )
	{
		cout << "Incorrect generator string! Switching to DEFAULT..." << endl;
		Generator = "DEFAULT";
	}
	
	if ( (Generator == "LAQGSM") || (Generator == "QGSM") )
	{
		if (Tracking == "HP")
		{
			if (fEnergy < 7.0) // not ready
			{
				parElPosMom->SetParameters(17.6,-0.12,0.078,0.167,0.00); // QGSM 5-9 gev
				parElNegMom->SetParameters(16.3,-0.12,0.078,0.167,0.00);
				parMuPosMom->SetParameters(20.5,0.064,0.107,0.05,0.105); // QGSM 5-9 gev
				parMuNegMom->SetParameters(20.5,0.064,0.107,0.05,0.105);
				parPiPosMom->SetParameters(307.0,0.035,0.175,0.127,0.139); // QGSM 5 gev
				parPiNegMom->SetParameters(325.6,0.035,0.175,0.127,0.139); // QGSM 5 gev
				parKaPosMom->SetParameters(15.3,0.236,0.203,0.056,0.494); // QGSM 5 gev
				parKaNegMom->SetParameters(8.88,0.236,0.203,0.056,0.494); // QGSM 5 gev
				amplParam = 104.0;
				parPrPosMom->SetParameters(amplParam,0.213,0.294,0.09,0.938); // QGSM 5 gev
				amplParam /= prrat;
				parPrNegMom->SetParameters(amplParam,0.213,0.294,0.09,0.938); // QGSM 5 gev
				parDeMom->SetParameters(5.7,0.338,0.333,0.114,1.878); // QGSM 5 gev
				parTrMom->SetParameters(0.2,-0.35,0.723,0.2,2.81);
				parHe3Mom->SetParameters(0.36,-0.784,530.3,0.131,1.983);
				parHe4Mom->SetParameters(6.6e-03,0.27,0.2,1.42,3.51);
			}
			else /// fEnergy > 7.0 not ready
			{
				parPiPosMom->SetParameters(473.,0.034,0.187,0.469,0.139); // QGSM 9 gev
				parPiNegMom->SetParameters(501.6,0.034,0.187,0.469,0.139); // QGSM 9 gev
				parKaPosMom->SetParameters(21.1,0.157,0.241,0.043,0.494); // QGSM 9 gev
				parKaNegMom->SetParameters(12.25,0.157,0.241,0.043,0.494); // QGSM 9 gev
				amplParam = 67.4;
				parPrPosMom->SetParameters(amplParam,.02,0.365,0.01,0.938); // QGSM 9 gev
				amplParam /= prrat;
				parPrNegMom->SetParameters(amplParam,.02,0.365,0.01,0.938); // QGSM 9 gev
				parDeMom->SetParameters(1.8,0.05,0.432,0.163,1.878); // QGSM 9 gev
				parTrMom->SetParameters(0.2,-0.35,0.723,0.2,2.81);
				parHe3Mom->SetParameters(0.36,-0.784,530.3,0.131,1.983);
				parHe4Mom->SetParameters(6.6e-03,0.27,0.2,1.42,3.51);
			}
		}
		
		else /// Tracking == "CF"
		{
			if (fEnergy < 7.0) // not ready
			{
				parElPosMom->SetParameters(17.6,-0.12,0.078,0.167,0.00); // QGSM 5-9 gev
				parElNegMom->SetParameters(16.3,-0.12,0.078,0.167,0.00);
				parMuPosMom->SetParameters(20.5,0.064,0.107,0.05,0.105); // QGSM 5-9 gev
				parMuNegMom->SetParameters(20.5,0.064,0.107,0.05,0.105);
				parPiPosMom->SetParameters(307.0,0.035,0.175,0.127,0.139); // QGSM 5 gev
				parPiNegMom->SetParameters(325.6,0.035,0.175,0.127,0.139); // QGSM 5 gev
				parKaPosMom->SetParameters(15.3,0.236,0.203,0.056,0.494); // QGSM 5 gev
				parKaNegMom->SetParameters(8.88,0.236,0.203,0.056,0.494); // QGSM 5 gev
				amplParam = 104.0;
				parPrPosMom->SetParameters(amplParam,0.213,0.294,0.09,0.938); // QGSM 5 gev
				amplParam /= prrat;
				parPrNegMom->SetParameters(amplParam,0.213,0.294,0.09,0.938); // QGSM 5 gev
				parDeMom->SetParameters(5.7,0.338,0.333,0.114,1.878); // QGSM 5 gev
				parTrMom->SetParameters(0.2,-0.35,0.723,0.2,2.81);
				parHe3Mom->SetParameters(0.36,-0.784,530.3,0.131,1.983);
				parHe4Mom->SetParameters(6.6e-03,0.27,0.2,1.42,3.51);
			}
			else /// fEnergy > 7.0 not ready
			{
				parElPosMom->SetParameters(17.6,-0.12,0.078,0.167,0.00); // QGSM 5-9 gev
				parElNegMom->SetParameters(16.3,-0.12,0.078,0.167,0.00);
				parMuPosMom->SetParameters(20.5,0.064,0.107,0.05,0.105); // QGSM 5-9 gev
				parMuNegMom->SetParameters(20.5,0.064,0.107,0.05,0.105);
				parPiPosMom->SetParameters(473.,0.034,0.187,0.469,0.139); // QGSM 9 gev
				parPiNegMom->SetParameters(501.6,0.034,0.187,0.469,0.139); // QGSM 9 gev
				parKaPosMom->SetParameters(21.1,0.157,0.241,0.043,0.494); // QGSM 9 gev
				parKaNegMom->SetParameters(12.25,0.157,0.241,0.043,0.494); // QGSM 9 gev
				amplParam = 67.4;
				parPrPosMom->SetParameters(amplParam,.02,0.365,0.01,0.938); // QGSM 9 gev
				amplParam /= prrat;
				parPrNegMom->SetParameters(amplParam,.02,0.365,0.01,0.938); // QGSM 9 gev
				parDeMom->SetParameters(1.8,0.05,0.432,0.163,1.878); // QGSM 9 gev
				parTrMom->SetParameters(0.2,-0.35,0.723,0.2,2.81);
				parHe3Mom->SetParameters(0.36,-0.784,530.3,0.131,1.983);
				parHe4Mom->SetParameters(6.6e-03,0.27,0.2,1.42,3.51);
			}
		}
	}
	
	else if (Generator == "URQMD")
	{
		if (Tracking == "HP")
		{
			if (fEnergy < 7.0) // not ready
			{
				parElPosMom->SetParameters(0.,1.,1.,1.,1.);
				parElNegMom->SetParameters(0.,1.,1.,1.,1.);
				parMuPosMom->SetParameters(0.,1.,1.,1.,1.);
				parMuNegMom->SetParameters(0.,1.,1.,1.,1.);
				parPiPosMom->SetParameters(307.0,0.035,0.175,0.127,0.139); // QGSM 5 gev
				parPiNegMom->SetParameters(325.6,0.035,0.175,0.127,0.139); // QGSM 5 gev
				parKaPosMom->SetParameters(15.3,0.236,0.203,0.056,0.494); // QGSM 5 gev
				parKaNegMom->SetParameters(8.88,0.236,0.203,0.056,0.494); // QGSM 5 gev
				amplParam = 104.0;
				parPrPosMom->SetParameters(amplParam,0.213,0.294,0.09,0.938); // QGSM 5 gev
				amplParam /= prrat;
				parPrNegMom->SetParameters(amplParam,0.213,0.294,0.09,0.938); // QGSM 5 gev
				parDeMom->SetParameters(0.,1.,1.,1.,1.);
				parTrMom->SetParameters(0.,1.,1.,1.,1.);
				parHe3Mom->SetParameters(0.,1.,1.,1.,1.);
				parHe4Mom->SetParameters(0.,1.,1.,1.,1.);
			}
			else /// fEnergy > 7.0, parameterization 11 GeV (27/07/2017) 10K events
			{
				prrat = 52.4698;
				parElPosMom->SetParameters(0.,1.,1.,1.,1.);
				parElNegMom->SetParameters(0.,1.,1.,1.,1.);
				parMuPosMom->SetParameters(0.,1.,1.,1.,1.);
				parMuNegMom->SetParameters(0.,1.,1.,1.,1.);
				parPiPosMom->SetParameters(1050.82,1.07492,0.16913,0.354773,0.253396); Multiplicities[4] = 627950;
				parPiNegMom->SetParameters(1134.48,1.05525,0.170399,0.35685,0.241421); Multiplicities[5] = 668192;
				parKaPosMom->SetParameters(316.545,0.193559,0.359936,0.0945873,0.283851); Multiplicities[6] = 63758;
				parKaNegMom->SetParameters(174.667,0.280725,0.316105,0.101935,0.293752); Multiplicities[7] = 35483;
				amplParam = 872.525;
				parPrPosMom->SetParameters(amplParam,0.440378,0.475486,0.207794,0.440092); Multiplicities[8] = 170999;
				amplParam /= prrat;
				parPrNegMom->SetParameters(amplParam,0.440378,0.475486,0.207794,0.440092); Multiplicities[9] = 3259;
				parDeMom->SetParameters(0.,1.,1.,1.,1.);
				parTrMom->SetParameters(0.,1.,1.,1.,1.);
				parHe3Mom->SetParameters(0.,1.,1.,1.,1.);
				parHe4Mom->SetParameters(0.,1.,1.,1.,1.);
			}
		}
		
		else /// Tracking == "CF"
		{
			if (fEnergy < 7.0) // not ready
			{
				parElPosMom->SetParameters(0.,1.,1.,1.,1.);
				parElNegMom->SetParameters(0.,1.,1.,1.,1.);
				parMuPosMom->SetParameters(0.,1.,1.,1.,1.);
				parMuNegMom->SetParameters(0.,1.,1.,1.,1.);
				parPiPosMom->SetParameters(307.0,0.035,0.175,0.127,0.139); // QGSM 5 gev
				parPiNegMom->SetParameters(325.6,0.035,0.175,0.127,0.139); // QGSM 5 gev
				parKaPosMom->SetParameters(15.3,0.236,0.203,0.056,0.494); // QGSM 5 gev
				parKaNegMom->SetParameters(8.88,0.236,0.203,0.056,0.494); // QGSM 5 gev
				amplParam = 104.0;
				parPrPosMom->SetParameters(amplParam,0.213,0.294,0.09,0.938); // QGSM 5 gev
				amplParam /= prrat;
				parPrNegMom->SetParameters(amplParam,0.213,0.294,0.09,0.938); // QGSM 5 gev
				parDeMom->SetParameters(0.,1.,1.,1.,1.);
				parTrMom->SetParameters(0.,1.,1.,1.,1.);
				parHe3Mom->SetParameters(0.,1.,1.,1.,1.);
				parHe4Mom->SetParameters(0.,1.,1.,1.,1.);
			}
			else /// fEnergy > 7.0, parameterization 8 GeV (27/07/2017) 10K events
			{
				prrat = 282.25;
				parElPosMom->SetParameters(0.,1.,1.,1.,1.);
				parElNegMom->SetParameters(0.,1.,1.,1.,1.);
				parMuPosMom->SetParameters(0.,1.,1.,1.,1.);
				parMuNegMom->SetParameters(0.,1.,1.,1.,1.);
				parPiPosMom->SetParameters(3360.54,1.08086,0.151008,0.330264,0.351397); Multiplicities[4] = 2020338;
				parPiNegMom->SetParameters(3530.8,1.14233,0.147187,0.328013,0.358974); Multiplicities[5] = 2205162;
				parKaPosMom->SetParameters(1206.47,0.245233,0.333437,0.0996193,0.327909); Multiplicities[6] = 241612;
				parKaNegMom->SetParameters(529.028,0.288553,0.303136,0.0948728,0.376275); Multiplicities[7] = 106440;
				amplParam = 4408.45;
				parPrPosMom->SetParameters(amplParam,0.666617,0.416237,0.215083,0.487749); Multiplicities[8] = 870192;
				amplParam /= prrat;
				parPrNegMom->SetParameters(amplParam,0.666617,0.416237,0.215083,0.487749); Multiplicities[9] = 3083;
				parDeMom->SetParameters(0.,1.,1.,1.,1.);
				parTrMom->SetParameters(0.,1.,1.,1.,1.);
				parHe3Mom->SetParameters(0.,1.,1.,1.,1.);
				parHe4Mom->SetParameters(0.,1.,1.,1.,1.);
			}
		}
	}
	
	else if (Generator == "DEFAULT")
	{
		parElPosMom->SetParameters(0.,1.,1.,1.,1.);
		parElNegMom->SetParameters(0.,1.,1.,1.,1.);
		parMuPosMom->SetParameters(0.,1.,1.,1.,1.);
		parMuNegMom->SetParameters(0.,1.,1.,1.,1.);
		parPiPosMom->SetParameters(503.,0.035,0.203,0.668,0.139); // average 9 gev
		parPiNegMom->SetParameters(533.4,0.035,0.203,0.668,0.139); // average 9 gev
		parKaPosMom->SetParameters(29.3,0.17,0.27,0.06,0.494); // average 9 gev
		parKaNegMom->SetParameters(17.,0.17,0.27,0.06,0.494); // average 9 gev
		amplParam = 88.;
		parPrPosMom->SetParameters(amplParam,0.18,0.37,0.15,0.938); // average 9 gev
		amplParam /= prrat;
		parPrNegMom->SetParameters(amplParam,0.18,0.37,0.15,0.938); // average 9 gev
		parDeMom->SetParameters(0.,1.,1.,1.,1.);
		parTrMom->SetParameters(0.,1.,1.,1.,1.);
		parHe3Mom->SetParameters(0.,1.,1.,1.,1.);
		parHe4Mom->SetParameters(0.,1.,1.,1.,1.);
	}
	
	fgaus = new TF1("fgaus","gaus(0)",-1.,5.);
	fgaus2 = new TF2("fgaus2","[0]*TMath::Gaus(x,[1],[2])*TMath::Gaus(y,[3],[4])",-2.,10.,-1.,5.);
	fasymgaus = new TF1("fasymgaus", this, &MpdPid::AsymGaus, -1., 5., 4, "MpdPid", "AsymGaus");
	fasymgaus2 = new TF2("fasymgaus2", this, &MpdPid::AsymGaus2, -1., 5., -2., 10., 6, "MpdPid", "AsymGaus2");
}

Double_t MpdPid::GetDedxElParam(Double_t p){
   Double_t dedx=parElBB->Eval(p);
   if (fTracking)
   {
	   if (p<0.15) dedx *= 0.98;
	   if (p<0.1) dedx *= 1.025;
   }
   return dedx;
}

Double_t MpdPid::GetDedxMuParam(Double_t p){
   Double_t dedx=parMuBB->Eval(p);
   if (fTracking)
   {
	   if (p<0.1) dedx *= 0.96;
	   if (p>1.25) dedx *= 1.005;
	   if (p>1.9) dedx *= 0.985;
   }
   else
   {
	   if (p<0.15) dedx *= 0.97;
	   if (p<0.2) dedx *= 1.015;
	   if (p>1.35) dedx *= 1.005;
	   if (p>1.6) dedx *= 1.005;
	   if (p>1.9) dedx *= 0.985;
   }
   return dedx;
}

Double_t MpdPid::GetDedxPiParam(Double_t p)
{
	Double_t dedx=parPiBB->Eval(p);
	if (fTracking)
	{
		if (p<0.1) dedx *= 0.85;
		if (p<0.15) dedx *= 0.96;
		if (p<0.25) dedx *= 1.015;
		if (p<0.3) dedx *= 0.99;
		if (p>2.3) dedx *= 0.99;
		if (p>2.7) dedx *= 0.98;
	}
	else
	{
		if (p<0.1) dedx *= 0.895;
		if (p<0.15) dedx *= 0.955;
		if (p<0.25) dedx *= 1.02;
		if (p<0.3) dedx *= 0.99;
		if (p>1.7) dedx *= 1.005;
		if (p>2.5) dedx *= 0.99;
	}
   return dedx;
}

Double_t MpdPid::GetDedxKaParam(Double_t p)
{
	Double_t dedx=parKaBB->Eval(p);
	if (fTracking)
	{
		if (p<0.15) dedx *= 0.98; 
		if (p<0.25) dedx *= 1.045; 
		if (p<0.3) dedx *= 1.04; 
		if (p<0.45) dedx *= 0.99; 
		if (p>1.05) dedx *= 1.01; 
		if (p>2.) dedx *= 1.01;
	}
	else
	{
		if (p<0.15) dedx *= 0.98;
		if (p<0.2) dedx *= 0.97;
		if (p<0.25) dedx *= 1.025;
		if (p<0.3) dedx *= 1.02;
		if (p<0.4) dedx *= 0.99;
		if (p<0.45) dedx *= 0.99;
		if (p<0.5) dedx *= 1.01;
		if (p>1.05) dedx *= 1.015;
		if (p>1.5) dedx *= 0.985;
		if (p>1.8) dedx *= 0.99;
		if (p>2.1) dedx *= 0.99;
		if (p>2.2) dedx *= 0.99;
		if (p>2.4) dedx *= 0.99;
		if (p>2.7) dedx *= 0.985;
	}
	return dedx;
}

Double_t MpdPid::GetDedxPrParam(Double_t p)
{
	Double_t dedx=parPrBB->Eval(p);
	if (fTracking)
	{
		if (p<0.1) dedx *= 1.325;
		if (p<0.15) dedx *= 1.065; 
		if (p<0.2) dedx *= 1.185; 
		if (p<0.25) dedx *= 1.07; 
		if (p<0.3) dedx *= 0.96; 
		if (p<0.45) dedx *= 1.015;
		if (p>1.6) dedx *= 0.99; 
		if (p>2.1) dedx *= 1.02;
	}
	else
	{
		if (p<0.1) dedx *= 0.69;
		if (p<0.15) dedx *= 0.94;
		if (p<0.2) dedx *= 0.955;
		if (p<0.25) dedx *= 0.965;
		if (p<0.3) dedx *= 0.975;
		if (p<0.45) dedx *= 1.03;
		if (p<0.55) dedx *= 0.97;
		if (p<0.6) dedx *= 1.03;
		if (p<0.65) dedx *= 0.975;
		if (p<0.7) dedx *= 1.01;
		if (p>2.0) dedx *= 1.01;
		if (p>2.4) dedx *= 0.99;
	}
	return dedx;
}

Double_t MpdPid::GetDedxDeParam(Double_t p){
   Double_t dedx=parDeBB->Eval(p);
   if (p<0.25) dedx *= 0.83;
   return dedx;
}

Double_t MpdPid::GetDedxTrParam(Double_t p){
   Double_t dedx=parTrBB->Eval(p);
   if (p<0.5) dedx *= 0.91;
   return dedx;
}

Double_t MpdPid::GetDedxHe3Param(Double_t p){
   Double_t dedx=parHe3BB->Eval(p);
   if (p<0.35) dedx *= 0.88;
   return dedx;
}

Double_t MpdPid::GetDedxHe4Param(Double_t p){
   Double_t dedx=parHe4BB->Eval(p);
   if (p>0.0) dedx *= 1.12;
   return dedx;
}

Bool_t MpdPid::FillProbs(MpdTrack* track)
{
   if (track == 0) return (kFALSE);
   Double_t px=track->GetPx(),py=track->GetPy(),pz=track->GetPz();   
   Double_t p=TMath::Sqrt(px*px+py*py+pz*pz);       
///
/// NO parameterisation beyond p=3.0 GeV/c
/// ignore anti-d,-He3 and -He4 
///
   if (p > 3.0) return (kFALSE);
   Int_t charge = 1;
   if (track->GetPt() > 0) charge = -1;
   Int_t flag = track->GetTofFlag();
   Double_t dedx = track->GetdEdXTPC();
   Double_t eta = track->GetEta();
   
   if (flag == 2 || flag == 6){
      Double_t m2 = track->GetTofMass2();
      FillProbs(p,dedx,m2,charge);
   }else{
      FillProbs(p,dedx,charge);   
   }

   return kTRUE;
}

Bool_t MpdPid::FillProbs(MpdTrack* track, Double_t dedx){
   if (track == 0) return (kFALSE);
      
   Double_t px=track->GetPx(),py=track->GetPy(),pz=track->GetPz();   
   Double_t p=TMath::Sqrt(px*px+py*py+pz*pz);       
///
/// NO parameterisation beyond p=3.0 GeV/c
/// ignore anti-d,-He3 and -He4 
///
   if (p > 3.0) return (kFALSE);
   Int_t charge = 1;
   if (track->GetPt() > 0.) charge = -1;
      
   Int_t flag = track->GetTofFlag();
   Double_t eta = track->GetEta();
   
   if (flag == 2 || flag == 6){
      Double_t m2 = track->GetTofMass2();
      FillProbs(p,dedx,m2,charge);
   }else{
      FillProbs(p,dedx,charge);
   }

   return kTRUE;
}

Bool_t MpdPid::FillProbs(Double_t p, Double_t dedx, Int_t charge){
	
	///
	/// NO parameterisation beyond p=3.0 GeV/c
	/// ignore anti-d,-He3 and -He4 
	///
	
	if (p > 3.0) return (kFALSE);
	
	fCharge = charge;
	
	Double_t nel=0.,nmu=0.,npi=0.,nka=0.,npr=0.,nde=0.,ntr=0.,nhe3=0.,nhe4=0.;
	
	if (fCharge > 0) {
		nel=parElPosMom->Eval(p);
		nmu=parMuPosMom->Eval(p);
		npi=parPiPosMom->Eval(p);
		nka=parKaPosMom->Eval(p);
		npr=parPrPosMom->Eval(p);
		nde=parDeMom->Eval(p);
		ntr=parTrMom->Eval(p);
		nhe3=parHe3Mom->Eval(p);
		nhe4=parHe4Mom->Eval(p);
	}
	else if (fCharge < 0) {
		nel=parElNegMom->Eval(p);
		nmu=parMuNegMom->Eval(p);
		npi=parPiNegMom->Eval(p);
		nka=parKaNegMom->Eval(p);
		npr=parPrNegMom->Eval(p);
	}
	else return (kFALSE);
	
	///
	/// Params. for dE/dx sigma versus total momentum.
	/// These are koef*<dE/dx> , koef=0.07
	/// Deviations from Bethe-Bloch at low-p accounted by somewhat larger sigmas
	///
	
	Double_t emeanel=GetDedxElParam(p);
	Double_t emeanmu=GetDedxMuParam(p);
	Double_t emeanpi=GetDedxPiParam(p);
	Double_t emeanpr=GetDedxPrParam(p);
	Double_t emeanka=GetDedxKaParam(p);
	Double_t emeande=GetDedxDeParam(p);
	Double_t emeantr=GetDedxTrParam(p);
	Double_t emeanhe3=GetDedxHe3Param(p);
	Double_t emeanhe4=GetDedxHe4Param(p);
	
	Double_t sigeel,sigemu,sigepi,sigepr,sigeka,sigede,sigetr,sigehe3,sigehe4;
	Double_t fel=0.,fmu=0.,fpi=0.,fka=0.,fpr=0.,fde=0.,ftr=0.,fhe3=0.,fhe4=0.;
	Double_t fsum=0., cut=4.0;
	
	if (kSigmaEloss>0.1) cut = kSigmaEloss;
	else return kFALSE;
	
	sigede=fSigmaDedx_1;
	sigetr=fSigmaDedx_1;
	sigehe3=fSigmaDedx_1;
	sigehe4=fSigmaDedx_1;
	if (p<0.15)sigede=fSigmaDedx_2;
	if (p<0.45){sigede=fSigmaDedx_2; sigetr=fSigmaDedx_2; sigehe3=fSigmaDedx_2; sigehe4=fSigmaDedx_2;}
	
	if (!fTracking)
	{
		sigemu=fSigmaDedx_1; if (p<0.15) sigemu=fSigmaDedx_2;
		sigeel=fSigmaDedx_3;
		sigepi=fSigmaDedx_1;
		sigeka=fSigmaDedx_1;
		sigepr=fSigmaDedx_1;
		if (p<0.15){ sigepi=fSigmaDedx_2; sigepr=fSigmaDedx_2; sigeka=fSigmaDedx_2; }
	}
	else
	{
		sigepi=GetDedxWidthValue(p,1);
		sigeka=GetDedxWidthValue(p,2);
		sigepr=GetDedxWidthValue(p,3);
		sigeel=GetDedxWidthValue(p,4);
		sigemu=GetDedxWidthValue(p,5);
	}
	
	///
	/// Set prob=0. for differences greater than "n" of sigmas
	/// otherwise evaluation..
	fpi = GetDedxProb_asym(cut, p, dedx, npi, emeanpi, sigepi, 1);
	fka = GetDedxProb_asym(cut, p, dedx, nka, emeanka, sigeka, 2);
	fpr = GetDedxProb_asym(cut, p, dedx, npr, emeanpr, sigepr, 3);
	fel = GetDedxProb_asym(cut, p, dedx, nel, emeanel, sigeel, 4);
	fmu = GetDedxProb_asym(cut, p, dedx, nmu, emeanmu, sigemu, 5);
	fde = GetDedxProb_asym(cut, p, dedx, nde, emeande, sigede, 6);
	ftr = GetDedxProb_asym(cut, p, dedx, ntr, emeantr, sigetr, 7);
	fhe3 = GetDedxProb_asym(cut, p, dedx, nhe3, emeanhe3, sigehe3, 8);
	fhe4 = GetDedxProb_asym(cut, p, dedx, nhe4, emeanhe4, sigehe4, 9);
	
	///
	/// Normalization
	///
	
	fsum=fel+fmu+fpi+fka+fpr+fde+ftr+fhe3+fhe4;
	if (1.0e+8*fsum>0.){
		fProbEl = fel/fsum;
		fProbMu = fmu/fsum;
		fProbPi = fpi/fsum;
		fProbKa = fka/fsum;
		fProbPr = fpr/fsum;
		fProbDe = fde/fsum;
		fProbTr = ftr/fsum;
		fProbHe3 = fhe3/fsum;
		fProbHe4 = fhe4/fsum;
	} else {return kFALSE;}; /// outliers!
	
	return kTRUE;         
}

Bool_t MpdPid::FillProbs(Double_t p, Double_t dedx, Double_t m2, Int_t charge){
	
	///
	/// NO parameterisation beyond p=3.0 GeV/c
	/// ignore anti-d,-He3 and -He4 
	///
	
	if (p > 3.0) return (kFALSE);
	
	fCharge = charge;
	
	Double_t nel=0.,nmu=0.,npi=0.,nka=0.,npr=0.,nde=0.,ntr=0.,nhe3=0.,nhe4=0.;
	
	///
	/// particle multiplicities for positives and negatives separately
	///
	
	if (fCharge > 0) {
		nel=parElPosMom->Eval(p);
		nmu=parMuPosMom->Eval(p);
		npi=parPiPosMom->Eval(p);
		nka=parKaPosMom->Eval(p);
		npr=parPrPosMom->Eval(p);
		nde=parDeMom->Eval(p);
		ntr=parTrMom->Eval(p);
		nhe3=parHe3Mom->Eval(p);
		nhe4=parHe4Mom->Eval(p);
	}
	else if (fCharge < 0) {
		nel=parElNegMom->Eval(p);
		nmu=parMuNegMom->Eval(p);
		npi=parPiNegMom->Eval(p);
		nka=parKaNegMom->Eval(p);
		npr=parPrNegMom->Eval(p);
	}
	else return (kFALSE);
	
	///
	/// Params. for dE/dx sigma versus total momentum.
	/// These are koef*<dE/dx> , koef=0.06
	/// Deviations from Bethe-Bloch at low-p accounted by somewhat larger sigmas
	///
	
	Double_t emeanel=GetDedxElParam(p);
	Double_t emeanmu=GetDedxMuParam(p);
	Double_t emeanpi=GetDedxPiParam(p);
	Double_t emeanpr=GetDedxPrParam(p);
	Double_t emeanka=GetDedxKaParam(p);
	Double_t emeande=GetDedxDeParam(p);
	Double_t emeantr=GetDedxTrParam(p);
	Double_t emeanhe3=GetDedxHe3Param(p);
	Double_t emeanhe4=GetDedxHe4Param(p);
	
	Double_t sigeel,sigemu,sigepi,sigepr,sigeka,sigede,sigetr,sigehe3,sigehe4;
	
	if (!fTracking)
	{
		sigeel=fSigmaDedx_3;
		sigemu=fSigmaDedx_1; if (p<0.15) sigemu=fSigmaDedx_2;
		sigepi=fSigmaDedx_1;
		sigeka=fSigmaDedx_1;
		sigepr=fSigmaDedx_1;
		if (p<0.15) {sigepi=fSigmaDedx_2; sigepr=fSigmaDedx_2; sigeka=fSigmaDedx_2;}
	}
	else
	{
		sigepi=GetDedxWidthValue(p,1);
		sigeka=GetDedxWidthValue(p,2);
		sigepr=GetDedxWidthValue(p,3);
		sigeel=GetDedxWidthValue(p,4);
		sigemu=GetDedxWidthValue(p,5);
	}
	sigede=fSigmaDedx_1;
	sigetr=fSigmaDedx_1;
	sigehe3=fSigmaDedx_1;
	sigehe4=fSigmaDedx_1;
	
	if (p<0.15) sigede=fSigmaDedx_2;
	if (p<0.45){ sigede=fSigmaDedx_2; sigetr=fSigmaDedx_2; sigehe3=fSigmaDedx_2; sigehe4=fSigmaDedx_2; }
	
	Double_t p_calc = 3.0; /// Above p=3.0 GeV/c param. for sig_M2 is bad!
	if (p < p_calc) p_calc = p;
	
	Double_t sigmel=parElM2->Eval(p_calc), sigmmu=parMuM2->Eval(p_calc);
	Double_t sigmpi;
	if(p<=1.4) sigmpi=parPiLowPM2->Eval(p_calc); else sigmpi=parPiHighPM2->Eval(p_calc);
	Double_t sigmka=parKaM2->Eval(p_calc);
	Double_t sigmpr;
	if(p<=1.4) sigmpr=parPrLowPM2->Eval(p_calc); else sigmpr=parPrHighPM2->Eval(p_calc);
	Double_t sigmde=parDeM2->Eval(p_calc), sigmtr=parTrM2->Eval(p_calc);
	Double_t sigmhe3=parHe3M2->Eval(p_calc), sigmhe4=parHe4M2->Eval(p_calc);
	
	Double_t fel=0.,fmu=0.,fpi=0.,fka=0.,fpr=0.,fde=0.,ftr=0.,fhe3=0.,fhe4=0.;
	Double_t fsum=0., cut_dedx, cut_m2;
	
	if ( (kSigmaEloss > 0.1) && (kSigmaTof > 0.1) )
	{ cut_dedx = kSigmaEloss; cut_m2 = kSigmaTof;}
	else return kFALSE;
	
	///
	/// Set prob=0. for differences greater than n-sigmas
	/// otherwise evaluation..
	///
	
	Double_t xx, yy, distance;
	
	xx = (dedx/emeanel-1.)/sigeel;
	yy = (m2-0.0007)/sigmel;
	if ( (TMath::Abs(xx) < cut_dedx) && (TMath::Abs(yy) < cut_m2) ){
		fgaus2->SetParameters(nel,0.002,sigmel,1.,sigeel);
		fel=fgaus2->Eval(m2,dedx/emeanel);
	} else fel=0.;
	
	fpi = GetCombProb_asym(cut_dedx, cut_m2, p, dedx, m2, npi, emeanpi, 0.019, sigepi, sigmpi, 1);
	fka = GetCombProb_asym(cut_dedx, cut_m2, p, dedx, m2, nka, emeanka, 0.24, sigeka, sigmka, 2);
	fpr = GetCombProb_asym(cut_dedx, cut_m2, p, dedx, m2, npr, emeanpr, 0.887, sigepr, sigmpr, 3);
	fmu = GetCombProb_asym(cut_dedx, cut_m2, p, dedx, m2, nmu, emeanmu, 0.011, sigemu, sigmmu, 5);
	fde = GetCombProb_asym(cut_dedx, cut_m2, p, dedx, m2, nde, emeande, 3.54, sigede, sigmde, 6);
	ftr = GetCombProb_asym(cut_dedx, cut_m2, p, dedx, m2, ntr, emeantr, 7.87, sigede, sigmde, 7);
	fhe3 = GetCombProb_asym(cut_dedx, cut_m2, p, dedx, m2, nhe3, emeanhe3, 1.983, sigehe3, sigmhe3, 8);
	fhe4 = GetCombProb_asym(cut_dedx, cut_m2, p, dedx, m2, nhe4, emeanhe4, 3.51, sigehe4, sigmhe4, 9);
	
	///
	/// Normalization
	///
	
	fsum=fel+fmu+fpi+fka+fpr+fde+ftr+fhe3+fhe4;
	if (1.0e+8*fsum>0.){
		fProbEl = fel/fsum;
		fProbMu = fmu/fsum;
		fProbPi = fpi/fsum;
		fProbKa = fka/fsum;
		fProbPr = fpr/fsum;
		fProbDe = fde/fsum;
		fProbTr = ftr/fsum;
		fProbHe3 = fhe3/fsum;
		fProbHe4 = fhe4/fsum;
	} else {return kFALSE;};/// outliers!
	
	return kTRUE;
}

Long_t MpdPid::GetMaxProb() {
	Long_t pdg=211;
	Double_t pcut=0.501;
	const Int_t nCodes=9;
	Long_t codes[nCodes]={211,2212,321,13,11,1000010020,1000010030,1000020030,1000020040};
	Double_t probs[nCodes]={fProbPi,fProbPr,fProbKa,fProbMu,fProbEl,fProbDe,fProbTr,fProbHe3,fProbHe4};
	
	if (fProbPi > pcut)       pdg=211;
	else if (fProbPr > pcut)  pdg=2212;
	else if (fProbKa > pcut)  pdg=321;
	else if (fProbMu > pcut)  pdg=13;
	else if (fProbEl > pcut)  pdg=11;
	else if (fProbDe > pcut)  pdg=1000010020;
	else if (fProbTr > pcut)  pdg=1000010030;
	else if (fProbHe3 > pcut)  pdg=1000020030;
	else if (fProbHe4 > pcut) pdg=1000020040;
	else{
		Long_t tmp;
		for (Int_t i=1;i<nCodes;i++){
			if (probs[0]<probs[i]){
				tmp=codes[0];
				codes[0]=codes[i];
				codes[i]=tmp;
				tmp=probs[0];
				probs[0]=probs[i];
				probs[i]=tmp;
				}
			}
		pdg=codes[0];
   }
   
   return (fCharge*pdg);   
}

ClassImp(MpdPid);