//---------------------------------------------------------------------------
#define AutoWordHExp
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

class NSAutoWordViewExp ;

//---------------------------------------------------------------------------
class TAutoWordFormEx : public TForm
{

private:	// User declarations
public:		// User declarations
    NSAutoWordViewExp* pView;
               TAutoWordFormEx(HWND Parent, NSAutoWordViewExp* View): TForm(Parent)
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#endif