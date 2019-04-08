# Obj与mtl 3D文件格式详解


## OBJ文件

     obj文件格式是Wavefront公司为它的一套基于工作站的3D建模和动画软件"AdvancedVisualizer"开发的一种文件格式。

OBJ文件是一种标准的3D模型文件格式，很适合用于3D软件模型之间的互导。OBJ文件是一种文本文件格式，这就意味着你可以直接用写字板打开进行查看修改。目前几乎所有知名的3D软件都支持OBJ文件的读写，不过很多软件需要通过插件才能做到这一点。另外，作为一种优秀的文件格式，很多游戏引擎也都支持OBJ文件。
OBJ3.0格式支持多边形(Polygon)，直线(Lines)，表面(Surfaces)，和自由形态曲线(Free-form Curves)。直线和多角形通过它们的点来描述，曲线和表面则根据于它们的控制点和依附于曲线类型的额外信息来定义。这些信息支持规则和不规则的曲线，包括那些基于贝塞尔 (Bezier)曲线，B样条(B-spline)，基数(Cardinal/Catmull-Rom样条)，和泰勒方程(Taylor equations)的曲线。 

## OBJ文件特点 
　　-1- OBJ是一种3D模型文件，因此不包含动画、材质特性、贴图路径、动力学、粒子等信息。 
　　-2- OBJ文件主要支持多边形(Polygons)模型。 虽然OBJ文件也支持曲线(Curves)、表面(Surfaces)、点组材质(Point Group Materials)，但Maya导出的OBJ文件并不包括这些信息。 
　　-3- OBJ文件支持三个点以上的面，这一点很有用。 很多其它的模型文件格式只支持三个点的面，所以我们导入Maya的模型经常被三角化了，这对于我们对模型的再加工甚为不利。　　　　
    -4- OBJ文件支持法线和贴图坐标。 

## OBJ文件基本结构
OBJ文件不需要任何种文件头(File Header)，尽管经常使用几行文件信息的注释作为文件的开头。OBJ文件由一行行文本组成，注释行以一个“井”号(#)为开头，空格和空行可以随意加到文件中以增加文件的可读性。有字的行都由一两个标记字母也就是关键字 (Keyword)开头，关键字可以说明这一行是什么样的数据。多行可以逻辑地连接在一起表示一行，方法是在每一行最后添加一个连接符(\)。注意连接符(\)后面不能出现空格或tab格，否则将导致文件出错。 
 
下列关键字可以在OBJ文件使用【关键字根据数据类型排列，每个关键字有一段简短描述】 
顶点数据(Vertex data)： 
　-　v 几何体顶点 (Geometric vertices) 
　-　vt贴图坐标点 (Texture vertices) 
　-　vn顶点法线 (Vertex normals) 
　-　vp参数空格顶点 (Parameter space vertices) 

　自由形态曲线(Free-form curve)/表面属性(surface attributes): 
　-　deg度 (Degree) 
　-　bmat基础矩阵 (Basis matrix) 
　-　step步尺寸 (Step size) 
　-　cstype曲线或表面类型 (Curve or surface type) 

　元素(Elements): 
　-　p点 (Point) 
　-　l线 (Line) 
　-　f面 (Face) 
　-　curv曲线 (Curve) 
　-　curv2 2D曲线 (2D curve) 
　-　surf表面 (Surface) 

　自由形态曲线(Free-form curve)/表面主体陈述(surface body statements): 
　-　parm参数值 (Parameter values ) 
　-　trim外部修剪循环 (Outer trimming loop) 
　-　hole内部整修循环 (Inner trimming loop) 
　-　scrv特殊曲线 (Special curve) 
　-　sp特殊的点 (Special point) 
　-　end结束陈述 (End statement) 

　自由形态表面之间的连接(Connectivity betweenfree-form surfaces): 
　-　con连接 (Connect) 

　成组(Grouping): 
　-　g组名称 (Group name) 
　-　s光滑组 (Smoothing group) 
　-　mg合并组 (Merging group) 
　-　o对象名称 (Object name) 

  显示(Display)/渲染属性(render attributes): 
　-　bevel导角插值 (Bevel interpolation) 
　-　c_interp颜色插值 (Color interpolation) 
　-　d_interp溶解插值 (Dissolve interpolation) 
　-　lod细节层次 (Level of detail) 
　-　usemtl材质名称 (Material name) 
　-　mtllib材质库 (Material library) 
　-　shadow_obj投射阴影 (Shadow casting) 
　-　trace_obj光线跟踪 (Ray tracing) 
　-　ctech曲线近似技术 (Curve approximation technique) 
　-　stech表面近似技术 (Surface approximation technique) 



## .mtl文件

三维模型处理会要读取.mtl文件来获得材质信息。

   .mtl文件（Material Library File）是材质库文件，描述的是物体的材质信息，ASCII存储，任何文本编辑器可以将其打开和编辑。一个.mtl文件可以包含一个或多个材质定义，对于每个材质都有其颜色，纹理和反射贴图的描述，应用于物体的表面和顶点。

以下是一个材质库文件的基本结构：

newmtl mymtl_1
  - 材质颜色光照定义
  - 纹理贴图定义
  - 反射贴图定义
newmtl mymtl_2
  - 材质颜色光照定义
  - 纹理贴图定义
  - 反射贴图定义
newmtl mymtl_3
  - 材质颜色光照定义
  - 纹理贴图定义
  - 反射贴图定义
……
注释：每个材质库可含多个材质定义，每个材质都有一个材质名。用newmtl mtlName来定义一个材质。对于每个材质，可定义它的颜色光照纹理反射等描述特征。
主要的定义格式如下文所示：
材质颜色光照
1.  环境反射有以下三种描述格式，三者是互斥的，不能同时使用。

  - Ka r g b    \\用RGB颜色值来表示，g和b两参数是可选的，如果只指定了r的值，则g和b的值都等于r的值。三个参数一般取值范围为0.0~1.0，在此范围外的值则相应的增加或减少反射率;
  - Ka spectral file.rfl factor   \\用一个rfl文件来表示。factor是一个可选参数，表示.rfl文件中值的乘数，默认为1.0;
  - Ka xyz x y z   \\用CIEXYZ值来表示，x，y，z是CIEXYZ颜色空间的各分量值。y和z两参数是可选的，如果只指定了x的值，则y和z的值都等于r的值。三个参数一般取值范围为0~1。

2. 漫反射描述的三种格式：
  - Kd r g b
  - Kd spectral file.rfl factor
  - Kd xyz x y z

3. 镜反射描述的三种格式:
  - Ks r g b
  - Ks spectral file.rfl factor
  - Ks xyz x y z

4. 滤光透射率描述的三种格式：
  - Tf r g b
  - Tf spectral file.rfl factor
  - Tf xyz x y z

5. 光照模型描述格式：
illum illum_#
指定材质的光照模型。illum后面可接0~10范围内的数字参数。

2.  map_Kd -options args filename
为漫反射指定颜色纹理文件(.mpc)或程序纹理文件(.cxc)，或是一个位图文件。作用原理与可选参数与map_Ka同。

3.  map_Ks -options args filename
为镜反射指定颜色纹理文件(.mpc)或程序纹理文件(.cxc)，或是一个位图文件。作用原理与可选参数与map_Ka同。

4.  map_Ns -options args filename
为镜面反射指定标量纹理文件（.mps或.cxs）。可选参数如下所示：
  - blendu on | off
  - blendv on | off
  - clamp on | off
  - imfchan r | g | b | m | l | z
  - mm base gain
  - o u v w
  - s u v w
  - t u v w
  - texres value

5. map_d -options args filename
  为消隐指数指定标量纹理文件（.mps或.cxs）。作用原理和可选参数与map_Ns同。

6. map_aat on
  打开纹理反走样功能。


材质指定凹凸纹理文件（.mpb或.cxb）,或是一个位图文件。
可选参数可为：
  - bm mult
  - clamp on | off
  - blendu on | off
  - blendv on | off
  - imfchan r | g | b | m | l | z
  - mm base gain
  - o u v w
  - s u v w
  - t u v w
  - texres value

******************************************************************************************************
反射贴图
在.mtl文件中的定义格式为：
1. refl -type sphere -options -args filename
指定一个球体区域将指定的纹理反射映射至物体。filename为一个颜色纹理文件，或可以映射的位图。

2. refl -type cube_side -options -args filenames
指定一个立方体区域将指定的纹理反射映射至物体。可以通过以下方式来指定纹理位置：
 -  refl -type cube_top
 - refl -type cube_bottom
 - refl -type cube_front
 - refl -type cube_back
 - refl -type cube_left
 - refl -type cube_right

"refl"可以单独使用，或配合以下参数使用。使用时将参数置于“refl”和“filename”之间。
 - blendu on | off
 - blendv on | off
 - cc on | off
 - clamp on | off
 - mm base gain
 - o u v w
 - s u v w
 - t u v w
 - texres value