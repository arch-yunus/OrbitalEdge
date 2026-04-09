const planets = [
    { name: 'Gunes', lon: 185.4, alt: 42.1, az: 178.9, sign: 'Terazi' },
    { name: 'Ay', lon: 42.1, alt: 15.2, az: 210.5, sign: 'Boga' },
    { name: 'Merkur', lon: 195.2, alt: 38.4, az: 165.2, sign: 'Akrep' },
    { name: 'Venus', lon: 210.5, alt: 30.1, az: 145.8, sign: 'Yay' },
    { name: 'Mars', lon: 245.8, alt: 12.5, az: 230.1, sign: 'Oglak' },
    { name: 'Jupiter', lon: 30.1, alt: 5.4, az: 120.3, sign: 'Boga' },
    { name: 'Saturn', lon: 310.2, alt: -10.2, az: 280.4, sign: 'Kova' }
];

function initDashboard() {
    const planetList = document.getElementById('planetList');
    const skyMap = document.getElementById('skyMap');

    planets.forEach(p => {
        // Kart Oluştur
        const card = document.createElement('div');
        card.className = 'card';
        card.innerHTML = `
            <h3>${p.name}</h3>
            <div class="val">${p.sign}</div>
            <div class="val" style="font-size: 0.8rem; color: #9ca3af; margin-top: 5px;">
                Alt: ${p.alt}° | Az: ${p.az}°
            </div>
        `;
        planetList.appendChild(card);

        // Sky Map Dot Oluştur (Eğer ufuk üstündeyse)
        if (p.alt > 0) {
            const dot = document.createElement('div');
            dot.className = 'planet_dot';
            
            // X (Azimut 0-360 -> 0-100%)
            const x = (p.az / 360) * 100;
            // Y (Yükseklik 0-90 -> 100-0%)
            const y = 100 - (p.alt / 90) * 100;

            dot.style.left = `${x}%`;
            dot.style.top = `${y}%`;
            dot.title = p.name;
            
            skyMap.appendChild(dot);
        }
    });

    // Zamanı Güncelle
    updateTime();
    setInterval(updateTime, 1000);
}

function updateTime() {
    const now = new Date();
    document.getElementById('lst').innerText = now.getUTCHours().toString().padStart(2, '0') + ":" + 
                                              now.getUTCMinutes().toString().padStart(2, '0');
}

document.addEventListener('DOMContentLoaded', initDashboard);
