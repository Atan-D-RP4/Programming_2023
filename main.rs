use std::f32;
use std::fs::File;
use std::io::Write;

const MAX_RAY_DEPTH: i32 = 5;

#[derive(Debug, Clone, Copy)]
struct Vec3 {
    x: f32,
    y: f32,
    z: f32,
}

impl Vec3 {
    fn new(x: f32, y: f32, z: f32) -> Self {
        Vec3 { x, y, z }
    }

    fn zero() -> Self {
        Vec3::new(0.0, 0.0, 0.0)
    }

    fn uniform(val: f32) -> Self {
        Vec3::new(val, val, val)
    }

    fn normalize(&mut self) -> &mut Self {
        let nor2 = self.length2();
        if nor2 > 0.0 {
            let inv_nor = 1.0 / nor2.sqrt();
            self.x *= inv_nor;
            self.y *= inv_nor;
            self.z *= inv_nor;
        }
        self
    }

    fn normalized(mut self) -> Self {
        self.normalize();
        self
    }

    fn dot(&self, other: &Vec3) -> f32 {
        self.x * other.x + self.y * other.y + self.z * other.z
    }

    fn length2(&self) -> f32 {
        self.x * self.x + self.y * self.y + self.z * self.z
    }

    fn length(&self) -> f32 {
        self.length2().sqrt()
    }
}

impl std::ops::Add for Vec3 {
    type Output = Vec3;

    fn add(self, other: Vec3) -> Vec3 {
        Vec3::new(self.x + other.x, self.y + other.y, self.z + other.z)
    }
}

impl std::ops::Sub for Vec3 {
    type Output = Vec3;

    fn sub(self, other: Vec3) -> Vec3 {
        Vec3::new(self.x - other.x, self.y - other.y, self.z - other.z)
    }
}

impl std::ops::Mul<f32> for Vec3 {
    type Output = Vec3;

    fn mul(self, scalar: f32) -> Vec3 {
        Vec3::new(self.x * scalar, self.y * scalar, self.z * scalar)
    }
}

impl std::ops::Mul<Vec3> for Vec3 {
    type Output = Vec3;

    fn mul(self, other: Vec3) -> Vec3 {
        Vec3::new(self.x * other.x, self.y * other.y, self.z * other.z)
    }
}

impl std::ops::AddAssign for Vec3 {
    fn add_assign(&mut self, other: Vec3) {
        self.x += other.x;
        self.y += other.y;
        self.z += other.z;
    }
}

impl std::ops::MulAssign<Vec3> for Vec3 {
    fn mul_assign(&mut self, other: Vec3) {
        self.x *= other.x;
        self.y *= other.y;
        self.z *= other.z;
    }
}

impl std::ops::Neg for Vec3 {
    type Output = Vec3;

    fn neg(self) -> Vec3 {
        Vec3::new(-self.x, -self.y, -self.z)
    }
}

#[derive(Debug, Clone)]
struct Sphere {
    center: Vec3,
    radius: f32,
    radius2: f32,
    surface_color: Vec3,
    emission_color: Vec3,
    transparency: f32,
    reflection: f32,
}

impl Sphere {
    fn new(
        center: Vec3,
        radius: f32,
        surface_color: Vec3,
        reflection: f32,
        transparency: f32,
        emission_color: Vec3,
    ) -> Self {
        Sphere {
            center,
            radius,
            radius2: radius * radius,
            surface_color,
            emission_color,
            transparency,
            reflection,
        }
    }

    fn intersect(&self, ray_orig: &Vec3, ray_dir: &Vec3) -> Option<(f32, f32)> {
        let l = self.center - *ray_orig;
        let tca = l.dot(ray_dir);
        if tca < 0.0 {
            return None;
        }
        let d2 = l.dot(&l) - tca * tca;
        if d2 > self.radius2 {
            return None;
        }
        let thc = (self.radius2 - d2).sqrt();
        let t0 = tca - thc;
        let t1 = tca + thc;
        Some((t0, t1))
    }
}

fn mix(a: f32, b: f32, mix_val: f32) -> f32 {
    b * mix_val + a * (1.0 - mix_val)
}

fn trace(ray_orig: &Vec3, ray_dir: &Vec3, spheres: &[Sphere], depth: i32) -> Vec3 {
    let mut tnear = f32::INFINITY;
    let mut closest_sphere: Option<&Sphere> = None;

    // Find intersection of this ray with the sphere in the scene
    for sphere in spheres {
        if let Some((mut t0, t1)) = sphere.intersect(ray_orig, ray_dir) {
            if t0 < 0.0 {
                t0 = t1;
            }
            if t0 < tnear {
                tnear = t0;
                closest_sphere = Some(sphere);
            }
        }
    }

    // If there's no intersection return background color
    if let Some(sphere) = closest_sphere {
        let mut surface_color = Vec3::zero();
        let phit = *ray_orig + *ray_dir * tnear; // point of intersection
        let mut nhit = (phit - sphere.center).normalized(); // normal at the intersection point

        // If the normal and the view direction are not opposite to each other
        // reverse the normal direction. That also means we are inside the sphere so set
        // the inside bool to true.
        let bias = 1e-4f32; // add some bias to the point from which we will be tracing
        let inside = if ray_dir.dot(&nhit) > 0.0 {
            nhit = -nhit;
            true
        } else {
            false
        };

        if (sphere.transparency > 0.0 || sphere.reflection > 0.0) && depth < MAX_RAY_DEPTH {
            let facing_ratio = -ray_dir.dot(&nhit);
            // change the mix value to tweak the effect
            let fresnel_effect = mix((1.0 - facing_ratio).powf(3.0), 1.0, 0.1);
            // compute reflection direction
            let refl_dir = (*ray_dir - nhit * 2.0 * ray_dir.dot(&nhit)).normalized();
            let reflection = trace(&(phit + nhit * bias), &refl_dir, spheres, depth + 1);
            let mut refraction = Vec3::zero();

            // if the sphere is also transparent compute refraction ray (transmission)
            if sphere.transparency > 0.0 {
                let ior = 1.1f32;
                let eta = if inside { ior } else { 1.0 / ior };
                let cosi = -nhit.dot(ray_dir);
                let k = 1.0 - eta * eta * (1.0 - cosi * cosi);
                let refr_dir = (*ray_dir * eta + nhit * (eta * cosi - k.sqrt())).normalized();
                refraction = trace(&(phit - nhit * bias), &refr_dir, spheres, depth + 1);
            }

            // the result is a mix of reflection and refraction (if the sphere is transparent)
            surface_color = (reflection * fresnel_effect
                + refraction * (1.0 - fresnel_effect) * sphere.transparency)
                * sphere.surface_color;
        } else {
            // it's a diffuse object, no need to raytrace any further
            for light_sphere in spheres {
                if light_sphere.emission_color.x > 0.0 {
                    // this is a light
                    let mut transmission = Vec3::uniform(1.0);
                    let light_direction = (light_sphere.center - phit).normalized();

                    for other_sphere in spheres {
                        if std::ptr::eq(light_sphere, other_sphere) {
                            continue;
                        }
                        if other_sphere
                            .intersect(&(phit + nhit * bias), &light_direction)
                            .is_some()
                        {
                            transmission = Vec3::zero();
                            break;
                        }
                    }

                    surface_color += sphere.surface_color
                        * transmission
                        * 0.0f32.max(nhit.dot(&light_direction))
                        * light_sphere.emission_color;
                }
            }
        }

        surface_color + sphere.emission_color
    } else {
        Vec3::uniform(2.0)
    }
}

fn render(spheres: &[Sphere]) {
    let width = 640u32;
    let height = 480u32;
    let mut image = vec![Vec3::zero(); (width * height) as usize];
    let inv_width = 1.0 / width as f32;
    let inv_height = 1.0 / height as f32;
    let fov = 30.0f32;
    let aspect_ratio = width as f32 / height as f32;
    let angle = (std::f32::consts::PI * 0.5 * fov / 180.0).tan();

    // Trace rays
    for y in 0..height {
        for x in 0..width {
            let xx = (2.0 * ((x as f32 + 0.5) * inv_width) - 1.0) * angle * aspect_ratio;
            let yy = (1.0 - 2.0 * ((y as f32 + 0.5) * inv_height)) * angle;
            let ray_dir = Vec3::new(xx, yy, -1.0).normalized();
            let pixel_index = (y * width + x) as usize;
            image[pixel_index] = trace(&Vec3::zero(), &ray_dir, spheres, 0);
        }
    }

    // Save result to a PPM image
    let mut file = File::create("./untitled.ppm").expect("Could not create file");
    writeln!(file, "P6\n{} {}\n255", width, height).expect("Could not write header");

    for pixel in &image {
        let r = ((pixel.x.min(1.0) * 255.0) as u8);
        let g = ((pixel.y.min(1.0) * 255.0) as u8);
        let b = ((pixel.z.min(1.0) * 255.0) as u8);
        file.write_all(&[r, g, b])
            .expect("Could not write pixel data");
    }
}

fn main() {
    let mut spheres = Vec::new();

    // position, radius, surface color, reflectivity, transparency, emission color
    spheres.push(Sphere::new(
        Vec3::new(0.0, -10004.0, -20.0),
        10000.0,
        Vec3::new(0.20, 0.20, 0.20),
        0.0,
        0.0,
        Vec3::zero(),
    ));
    spheres.push(Sphere::new(
        Vec3::new(0.0, 0.0, -20.0),
        4.0,
        Vec3::new(1.00, 0.32, 0.36),
        1.0,
        0.5,
        Vec3::zero(),
    ));
    spheres.push(Sphere::new(
        Vec3::new(5.0, -1.0, -15.0),
        2.0,
        Vec3::new(0.90, 0.76, 0.46),
        1.0,
        0.0,
        Vec3::zero(),
    ));
    spheres.push(Sphere::new(
        Vec3::new(5.0, 0.0, -25.0),
        3.0,
        Vec3::new(0.65, 0.77, 0.97),
        1.0,
        0.0,
        Vec3::zero(),
    ));
    spheres.push(Sphere::new(
        Vec3::new(-5.5, 0.0, -15.0),
        3.0,
        Vec3::new(0.90, 0.90, 0.90),
        1.0,
        0.0,
        Vec3::zero(),
    ));
    // light
    spheres.push(Sphere::new(
        Vec3::new(0.0, 20.0, -30.0),
        3.0,
        Vec3::zero(),
        0.0,
        0.0,
        Vec3::uniform(3.0),
    ));

    render(&spheres);
}
