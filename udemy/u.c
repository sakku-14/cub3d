func setup()
{

}

func update()
{

}

func draw()
{
    update();
    
}

long deg_to_rad(long degrees)
{
    return (degrees * (pi / 180));
}

long rad_to_deg(long rad)
{
    return (rad * (180 / pi));
}

fov_angle = 60 * (pi / 180);
num_rays = 320;
ray_angle = fov_angle / num_rays;