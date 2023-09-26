#define D 0x0000
#define P 0x8177
#define B 0x3457
#define O 0xfcc7
#define Y 0xff27
#define G 0x8410
#define L 0xd6ba
#define W 0xffff

short int Character[17][16]={
		{W, W, W, W, W, W, D, D, D, D, D, W, W, W, W, W},
		{W, W, W, W, D, D, P, P, P, W, W, D, D, W, W, W},
		{W, W, W, D, P, P, P, P, P, P, P, P ,P, D, W, W},
		{W, W, W, D, P, P, D, D, D, D, D, D, D, D, W, W},
		{W, W, D, P, P, D, D, W, W, W, D, W, W, W, D, W},
		{D, D, D, P, P, D, W, W, W, D, W, W, D, W, W, D},
		{D, G, D, P, P, D, W, W, W, W, W, W, W, W, W, D},
		{D, G, D, P, P, D, L, W, W, W, W, W, W, W, W, D},
		{D, G, G, D, D, B, D, L, L, L, D, L, L, L, D, W},
		{D, G, G, D, B, B, B, D, D, D, B, D, D, D, W, W},
		{D, G, G, D, D, B, B, B, B, B, B, B, B, D, W, W},
		{D, G, D, W, W, D, B, B, D, D, D, D, D, W, D, W},
		{D, G, D, W, W, D, B, B, B, B, B, B, D, W, D, W},
		{D, D, D, D, D, B, B, B, B, B, B, B, D, D, W, W},
		{W, O, O, O, D, B, B, B, D, B, B, D, W, W, W, W},
		{W, Y, O, Y, W, D, D, D, D, D, D, W, W, W, W, W},
		{W, W, Y, W, W, W, W, W, W, W, W, W, W, W, W, W}
	};
	int track=1;
	int x_location=100;
	int y_location=100;
    int main(){
        for(int i=0; i<17; i++){
			for(int j=0; j<16; j++){
				plot_pixel(x_location+j, y_location+i, Character[i][j]);
			}
	    }
    }