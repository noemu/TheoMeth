#version 330								
#define sixty 1.047198						
in vec2 texCoords;							
layout(location = 0) out vec4 frag_color;	
void main() {								
	
	//define center
	vec2 center = vec2(0.5);

	//calculate distance form current texture position to center
	float tc = distance(center,texCoords)*2.0;

	vec2 direction = texCoords - center;
	
	//calculate  H S V according to wikipedia
	float H = degrees(atan(direction.y, direction.x))+180.0;
	float S = tc;
	float V = 1.0;

	//calculate the part (it is used here as a sort of ID) of the hexagon in which the hue (H) value is located
	int hi = int(floor(H/60.0));			
	
	float f = (H / 60.0 - float(hi));
	//compute the 

	float p = V*(1.0 - S);
	float q = V*(1.0 - S*f);
	float t = V*(1.0 - S*(1.0 - f));


	float R = 0;
	float G = 0;
	float B = 0;

	if (S>1.0) {							
		vec4(0.0, 0, 0, 1); return;
	}

	//set the appropriate RGB values. Consider that there are 6 areas that should the distinguished.
	if (hi==0 || hi==6) {					
		R = V;
		G = t;
		B = p;
	}										
	else if (hi==1) {		
		R = q;
		G = V;
		B = p;				
	}										
	else if (hi==2) {		
		R = p;
		G = V;
		B = t;					
	}									
	else if (hi==3) {		
		R = p;
		G = q;
		B = V;					
	}										
	else if (hi==4) {		
		R = t;
		G = p;
		B = V;					
	}										
	else if (hi==5) {				
		R = V;
		G = p;
		B = q;				
	}

	frag_color = vec4(R,G,B,1);
}