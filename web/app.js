const planets = [
    { name: 'Gunes', lon: 185.4, alt: 42.1, az: 178.9, sign: 'Terazi', color: '#f59e0b' },
    { name: 'Ay', lon: 42.1, alt: 15.2, az: 210.5, sign: 'Boga', color: '#f3f4f6' },
    { name: 'Merkur', lon: 195.2, alt: 38.4, az: 165.2, sign: 'Akrep', color: '#9ca3af' },
    { name: 'Venus', lon: 210.5, alt: 30.1, az: 145.8, sign: 'Yay', color: '#3b82f6' },
    { name: 'Mars', lon: 245.8, alt: 12.5, az: 230.1, sign: 'Oglak', color: '#ef4444' },
    { name: 'Jupiter', lon: 30.1, alt: 5.4, az: 120.3, sign: 'Boga', color: '#fb923c' },
    { name: 'Saturn', lon: 310.2, alt: -10.2, az: 280.4, sign: 'Kova', color: '#a8a29e' }
];

function initDashboard() {
    const planetList = document.getElementById('planetList');
    const skyMapContainer = document.getElementById('skyMap');
    
    // Canvas Kurulumu
    const canvas = document.createElement('canvas');
    canvas.id = 'skyCanvas';
    skyMapContainer.appendChild(canvas);
    const ctx = canvas.getContext('2d');

    function resize() {
        canvas.width = skyMapContainer.clientWidth;
        canvas.height = skyMapContainer.clientHeight;
    }
    window.addEventListener('resize', resize);
    resize();

    function draw() {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        
        // Izgara (Grid) Cizimi
        ctx.strokeStyle = 'rgba(255,255,255,0.05)';
        ctx.beginPath();
        for(let i=0; i<=10; i++) {
            let y = (i/10) * canvas.height;
            ctx.moveTo(0, y);
            ctx.lineTo(canvas.width, y);
        }
        ctx.stroke();

        // Gezegenleri Ciz
        planets.forEach(p => {
            if (p.alt > 0) {
                const x = (p.az / 360) * canvas.width;
                const y = canvas.height - (p.alt / 90) * canvas.height;

                // Parlama Efekti
                const grad = ctx.createRadialGradient(x, y, 0, x, y, 15);
                grad.addColorStop(0, p.color);
                grad.addColorStop(1, 'transparent');
                
                ctx.fillStyle = grad;
                ctx.beginPath();
                ctx.arc(x, y, 15, 0, Math.PI * 2);
                ctx.fill();

                ctx.fillStyle = '#fff';
                ctx.font = '10px Outfit';
                ctx.fillText(p.name, x + 10, y - 10);
            }
        });

        requestAnimationFrame(draw);
    }

    // Kartlari Olustur
    planets.forEach(p => {
        const card = document.createElement('div');
        card.className = 'card';
        card.innerHTML = `<h3>${p.name}</h3><div class="val">${p.sign}</div>`;
        planetList.appendChild(card);
    });

    draw();
    updateTime();
    setInterval(updateTime, 1000);
}

function updateTime() {
    const now = new Date();
    document.getElementById('lst').innerText = now.getUTCHours().toString().padStart(2, '0') + ":" + 
                                              now.getUTCMinutes().toString().padStart(2, '0');
}

document.addEventListener('DOMContentLoaded', initDashboard);
