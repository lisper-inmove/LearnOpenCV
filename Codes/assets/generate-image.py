# 简化版本 - 只需要PIL/Pillow
from PIL import Image, ImageDraw, ImageFont

def generate_images():
    # 方法1：包含A B C的图片
    img1 = Image.new('RGB', (80, 80), color='white')
    draw = ImageDraw.Draw(img1)
    
    # 设置字体大小
    try:
        font = ImageFont.truetype("arial.ttf", 80)
    except:
        font = ImageFont.load_default()
    
    text_abc = "A B C"
    # 计算文本位置使其居中
    bbox = draw.textbbox((0, 0), text_abc, font=font)
    text_width = bbox[2] - bbox[0]
    text_height = bbox[3] - bbox[1]
    x = (80 - text_width) / 2
    y = (80 - text_height) / 2
    
    draw.text((x, y), text_abc, fill='black', font=font)
    img1.save('ABC_image.png')
    print("✓ 已生成: ABC_image.png")
    
    # 方法2：单独A的图片
    img2 = Image.new('RGB', (20, 20), color='lightblue')
    draw2 = ImageDraw.Draw(img2)
    
    try:
        font2 = ImageFont.truetype("arial.ttf", 150)
    except:
        font2 = ImageFont.load_default()
    
    text_a = "A"
    bbox2 = draw2.textbbox((0, 0), text_a, font=font2)
    text_width2 = bbox2[2] - bbox2[0]
    text_height2 = bbox2[3] - bbox2[1]
    x2 = (20 - text_width2) / 2
    y2 = (20 - text_height2) / 2
    
    draw2.text((x2, y2), text_a, fill='darkred', font=font2)
    img2.save('A_image.png')
    print("✓ 已生成: A_image.png")

if __name__ == "__main__":
    try:
        generate_images()
        print("\n图片生成完成!")
    except Exception as e:
        print(f"生成图片时出错: {e}")
        print("\n请确保已安装Pillow库: pip install pillow")
